//
// Created by Gilberto Dougal on 5/10/21.
//

#include "Server.hpp"

Server::Server(const Config &cfg) {
	create_listen_socket(cfg);
	create_db_mask(cfg);
	logfile_ = open(cfg.getSection("LOGS_PATH").getStringVal("file").c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (logfile_ < 0)
		throw std::runtime_error("Can't create file");
}

Server::~Server() {
	close(listen_fd_);
	close(logfile_);
}

void Server::run_server() {
	bool is_any_set;
	while (true) {
		manage_client_fd();
		select(max_fd_ + 1, &read_fds_, &write_fds_, nullptr, nullptr);
		create_client();
		auto it = bridges_.begin();
		while (it != bridges_.end()) {
			if (FD_ISSET((*it)->getFd(), &read_fds_)) {
				(*it)->read_from_client();
			}
			else if (FD_ISSET((*it)->getFd(), &write_fds_)) {
				(*it)->send_to_client();
			}
			if ((*it)->getCurState() == state::FINALL) {
				it = bridges_.erase(it);
			}
			else {
				++it;
			}
		}
	}
}


void Server::manage_client_fd() {
	FD_ZERO(&read_fds_);
	FD_ZERO(&write_fds_);
	FD_SET(listen_fd_, &read_fds_);
	max_fd_ = listen_fd_;
	for (auto &item: bridges_) {
		FD_SET(item->getFd(), &read_fds_);
		FD_SET(item->getFd(), &write_fds_);
		max_fd_ = max_fd_ > item->getFd() ? max_fd_ : item->getFd();
		}
}

void Server::create_client() {
	int		new_client_fd;
	if (FD_ISSET(listen_fd_, &read_fds_)) {
		if ((new_client_fd = accept(listen_fd_, nullptr, nullptr)) < 0) {
			std::cerr << "Cant`t accept client" << std::endl;
			return;
		}
		fcntl(new_client_fd, F_SETFL, O_NONBLOCK);
		bridges_.emplace_back(new Client(new_client_fd, logfile_));
	}
}

void Server::close_fd_error(std::string except) {
	if (close(listen_fd_) < 0)
		throw std::runtime_error(except.append(" and error close"));
	throw std::runtime_error(except);
}

void Server::create_listen_socket(const Config &cfg) {
	struct sockaddr_in servaddr{};

	if ((listen_fd_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		throw std::runtime_error("Create socket error");
	}
	std::memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = cfg.getSection("SERVER").getAddrVal("ip");
	servaddr.sin_port = cfg.getSection("SERVER").getPortVal("port");
	int yes = 1;

	if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		close_fd_error("error setsockopt");
	}
	if ((bind(listen_fd_, (struct sockaddr *) &servaddr, sizeof servaddr)) == -1) {
		close_fd_error("bind error");
	}
	if (fcntl(listen_fd_, F_SETFL, O_NONBLOCK) < 0) {
		close_fd_error("fcntl error");
	}
	if (listen(listen_fd_, 15) < 0) {
		close_fd_error("listen error!");
	}
}

void Server::create_db_mask(const Config &cfg) {}
