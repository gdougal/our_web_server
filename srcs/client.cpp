//
// Created by Gilberto Dougal on 5/10/21.
//

#include "client.hpp"

Client::Client(int client_fd, int file, BaseClientHandler* type_client)  :
				fd_(client_fd),
				outfile_(file) {
	cur_state_ = state::READ_FROM_CLIENT;
	handler_ = type_client;
	g_recv_buffer = new char[PORTION_SIZE + 1];
}

Client::~Client() {
	close(fd_);
	delete handler_;
}

int					Client::getFd() const { return fd_; }
enum state	Client::getCurState() const { return cur_state_; }



void				Client::read_from_client() {
	bzero(g_recv_buffer, PORTION_SIZE + 1);
	static size_t buffer_len;
	buffer_len = recv(fd_, g_recv_buffer, PORTION_SIZE, 0);
	if (buffer_len <= 0 || buffer_len > PORTION_SIZE) {
		cur_state_ = state::FINALL;
		return;
	}
	buffer_.append(g_recv_buffer);
	if ( handler_->is_recvest_end(buffer_) ) {
		if ( handler_->query_parsing(buffer_) ) {
			handler_->logger(buffer_, outfile_); /// TODO:
			cur_state_ = state::SEND_TO_CLIENT;
		}
	}
}

void				Client::send_to_client(const server_config& data) {
	std::string http(handler_->create_response());
	buffer_.clear();
	if (send(fd_, http.c_str(), http.size(), 0)/*;*/ <= 0) {
		cur_state_ = state::FINALL;
		return ;
	}
	cur_state_ = state::READ_FROM_CLIENT;
};
