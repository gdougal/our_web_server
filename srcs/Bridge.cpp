//
// Created by Gilberto Dougal on 5/10/21.
//

#include "Bridge.hpp"

Client::Client(int client_fd, int file)  :
				fd_(client_fd),
				tmp_((new char[PORTION_SIZE])),
				outfile_(file) {
	cur_state_ = state::READ_FROM_CLIENT;
	handler_ = std::bind(&Client::read_from_client, this);
}

Client::~Client() {
	close(fd_);
}

void Client::caller(bool a) {
	if (a == true)
		handler_();
}

int Client::getFd() const { return fd_; };
enum state Client::getCurState() const { return cur_state_; };

void Client::read_from_client() {
	int	cur_read;
	buf_len_ = recv(fd_, tmp_.get(), PORTION_SIZE, 0);
	if (buf_len_ <= 0) {
		cur_state_ = state::FINALL;
	}
	logger();
	bufer_.insert(bufer_.end(), tmp_.get(), tmp_.get() + buf_len_);
	handler_ = std::bind(&Client::send_to_client, this);
	cur_state_ = state::SEND_TO_CLIENT;
}

void Client::send_to_client() {
	std::string body("<!DOCTYPE html>\n"
									 "<html lang=\"en\">\n"
									 "<head>\n"
									 "  <meta charset=\"UTF-8\">\n"
									 "  <title>Title</title>\n"
									 "</head>\n"
									 "<body>\n"
									 "Lolka tbl"
									 "</body>\n"
									 "</html>");
	std::string http(
					"HTTP/1.1 200 OK\r\n"
					"Version: HTTP/1.1\r\n"
		 			"Content-Type: text/html; charset=utf-8\r\n"
					"Content-Length: "
					+ std::to_string(body.length()) + "\r\n\r\n"
					+ body);
	send(fd_, http.c_str(), http.size(), 0);
	if (send(fd_, http.c_str(), http.size(), 0) < 0) {
		cur_state_ = state::FINALL;
		return ;
	}
	handler_ = std::bind(&Client::read_from_client, this);
	cur_state_ = state::READ_FROM_CLIENT;
	bufer_.clear();
};

void Client::logger() {
		write(outfile_, &(bufer_), buf_len_);
		write(outfile_, "\n\n", 2);
}
