//
// Created by Gilberto Dougal on 5/10/21.
//

#include "client.hpp"

Client::Client(int client_fd, int file, BaseClientHandler* type_client)  :
				fd_(client_fd),
				outfile_(file) {
	recv_buffer_ = new char[PORTION_SIZE + 1];
	cur_state_ = state::READ_FROM_CLIENT;
	handler_ = type_client;
}

Client::~Client() {
	close(fd_);
	delete[] recv_buffer_;
	delete handler_;
}

int					Client::getFd() const { return fd_; }
enum state	Client::getCurState() const { return cur_state_; }



void				Client::read_from_client() {
	bzero(recv_buffer_, PORTION_SIZE + 1);
	static size_t buffer_len;
	buffer_len = recv(fd_, recv_buffer_, PORTION_SIZE, 0);
	if (buffer_len <= 0 || buffer_len > PORTION_SIZE) {
		cur_state_ = state::FINALL;
		return;
	}
	buffer_.append(recv_buffer_);
	if (handler_->is_recvest_end(buffer_)) {
		handler_->query_parsing(buffer_);

		handler_->logger(buffer_, outfile_);

		buffer_.clear();
		cur_state_ = state::SEND_TO_CLIENT;
	}
}

void				Client::send_to_client() {
	std::string http(handler_->create_response());
	if (send(fd_, http.c_str(), http.size(), 0)/*;*/ <= 0) {
		cur_state_ = state::FINALL;
		return ;
	}
	cur_state_ = state::READ_FROM_CLIENT;
};
