//
// Created by Gilberto Dougal on 5/10/21.
//

#include "client.hpp"

Client::Client(int client_fd, int file)  :
				fd_(client_fd),
				outfile_(file) {
	tmp_ = new char[PORTION_SIZE + 1];
	cur_state_ = state::READ_FROM_CLIENT;
}

Client::~Client() {
	close(fd_);
	delete[] tmp_;
}


int					Client::getFd() const { return fd_; }
enum state	Client::getCurState() const { return cur_state_; }

void Client::query_parsing() {
	size_t pos = 0;
	methos_and_path_ = string_dirty_work::pair_maker(pos, bufer_, " ");
	pos = 0;
	pos =  string_dirty_work::next_line(pos, bufer_, "\n\r");
	for(; pos != bufer_.npos;) {
		pos = string_dirty_work::get_string_map(query_, bufer_, pos, " :", "\n\r");
	}
}


void				Client::read_from_client() {
	bzero(tmp_, PORTION_SIZE + 1);
	buf_len_ = recv(fd_, tmp_, PORTION_SIZE, 0);
	if (buf_len_ == 0 || buf_len_ > PORTION_SIZE) {
		cur_state_ = state::FINALL;
		return;
	}
	bufer_ += tmp_;
 	query_parsing();
	logger();
	bufer_.clear();
	cur_state_ = state::SEND_TO_CLIENT;
}

#include <fstream>
void				Client::send_to_client() {
	/* Before sending - create response. Use of parsing result. */
	if (methos_and_path_.second.empty())
		return ;
	std::ifstream	page("/Users/gdougal/Desktop/our_web_server" + methos_and_path_.second);
	std::cout << page.is_open() << std::endl;
	std::string		body;
	std::string		tmp;
	while (std::getline(page, tmp)) { body += tmp; };
	std::string http(
					"HTTP/1.1 200 OK\r\nVersion: HTTP/1.1\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: "
					+ std::to_string(body.length()) + "\r\n\r\n"
					+ body);
	std::cout << http.c_str() << std::endl;
	if (send(fd_, http.c_str(), http.size(), 0) < 0) {
		cur_state_ = state::FINALL;
		return ;
	}
	cur_state_ = state::READ_FROM_CLIENT;
};

void		Client::logger() {
		write(outfile_, bufer_.data(), bufer_.size());
		write(outfile_, "\n\n", 2);
		for(auto iter = query_.begin(); iter != query_.end(); ++iter) {
			write(outfile_, "Key: ", 5);
			write(outfile_, iter->first.data(), iter->first.size());
			write(outfile_, " Value: ", 8);
			write(outfile_, iter->second.data(), iter->second.size());
			write(outfile_, "\n", 1);
		}
	write(outfile_, "\n\n", 2);
}
