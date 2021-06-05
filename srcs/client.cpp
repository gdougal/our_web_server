//
// Created by Gilberto Dougal on 5/10/21.
//

#include "client.hpp"

Client::Client(int client_fd, int file)  :
				fd_(client_fd),
				outfile_(file) {
	tmp_ = new char[PORTION_SIZE + 1];
}

Client::~Client() {
	close(fd_);
	delete[] tmp_;
}


int					Client::getFd() const { return fd_; }
enum state	Client::getCurState() const { return cur_state_; }

void parsing(std::map<std::string, std::string>& schema, std::string& data) {
//	первый лайн обрезать (до \n - парсить отдельно, со второго - по :)
	/* 1) Понять какой запрос (GET, POST, DELETE)
	 * 2) проинициализировать/заполнить ключами (опционально значением), пример:
	 * schema["GET"] = "";
	 * schema["Connection"] = "";
	 * schema["Accept"] = ""; и т.д.
	 *  **если токенизировать строку то будет еще проще и можно вкидывать прямо токены а в значение - следующий;
	 * дальнейший парсинг можно проводить используя ключ */
}

void				Client::read_from_client() {
	bzero(tmp_, PORTION_SIZE + 1);
	buf_len_ = recv(fd_, tmp_, PORTION_SIZE, 0);
	if (buf_len_ == 0 || buf_len_ > PORTION_SIZE) {
		cur_state_ = state::FINALL;
		return;
	}
	/* Parsing query */
	bufer_ += tmp_;
	logger();
	bufer_.clear();
}

void				Client::send_to_client() {
	/* Before sending - create response. Use of parsing result. */
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
};

void		Client::logger() {
		write(outfile_, bufer_.data(), bufer_.size());
		write(outfile_, "\n\n", 2);
}
