//
// Created by Gilberto Dougal on 5/10/21.
//

#include "Server.hpp"

Server::Server(const Config &cfg) {
	listen_fd_ = fd_creator::create_listen_socket(cfg);
	logfile_ = open(cfg.getSection("LOGS_PATH").getStringVal("file").c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (logfile_ < 0)
		throw std::runtime_error("Can't create file");
}

Server::~Server() {
	close(listen_fd_);
	close(logfile_);
}

void Server::run_server() {
	while (true) {
		manage_client_fd();
		select(max_fd_ + 1, &read_fds_, &write_fds_, nullptr, nullptr);
		create_client();
		auto it = clients_.begin();
		while (it != clients_.end()) {
			if (FD_ISSET((*it)->getFd(), &read_fds_)) {
				(*it)->read_from_client();
			}
			else if (FD_ISSET((*it)->getFd(), &write_fds_)) {
				(*it)->send_to_client();
			}
			if ((*it)->getCurState() == state::FINALL) {
				it = clients_.erase(it);
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
	for (auto &item: clients_) {
		FD_SET(item->getFd(), &read_fds_);
		FD_SET(item->getFd(), &write_fds_);
		max_fd_ = max_fd_ > item->getFd() ? max_fd_ : item->getFd();
	}
}

void Server::create_client() {
	int		client_fd;
	if (FD_ISSET(listen_fd_, &read_fds_) &&
			(client_fd = fd_creator::create_client_fd(listen_fd_)) > 0) {

		clients_.emplace_back(new Client(client_fd, logfile_));
	}
}

