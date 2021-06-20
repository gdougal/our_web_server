//
// Created by Gilberto Dougal on 6/5/21.
//

#include "fd_creator.hpp"
#include "cstring"

namespace fd_creator {
	void close_fd_error(std::string except, int listen_fd_) {
		if (close(listen_fd_) < 0)
			throw std::runtime_error(except.append(" and error close"));
		throw std::runtime_error(except);
	}

	int create_client_fd(int listen_fd) {
		int		new_client_fd;
		if ((new_client_fd = accept(listen_fd, nullptr, nullptr)) < 0) {
			std::cerr << "Cant`t accept client" << std::endl;
			return -1;
		}
		fcntl(new_client_fd, F_SETFL, O_NONBLOCK);
		return new_client_fd;
	}

	int create_listen_socket(const ConfigParser &cfg) {
		int listen_fd_;
		struct sockaddr_in servaddr{};

		if ((listen_fd_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
			throw std::runtime_error("Create socket error");
		}
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = cfg.getSection("SERVER").getAddrVal("ip");
		servaddr.sin_port = cfg.getSection("SERVER").getPortVal("port");
		int yes = 1;

		if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			close_fd_error("error setsockopt", listen_fd_);
		}
		if ((bind(listen_fd_, (struct sockaddr *) &servaddr, sizeof servaddr)) == -1) {
			close_fd_error("bind error", listen_fd_);
		}
		if (fcntl(listen_fd_, F_SETFL, O_NONBLOCK) < 0) {
			close_fd_error("fcntl error", listen_fd_);
		}
		if (listen(listen_fd_, 15) < 0) {
			close_fd_error("listen error!", listen_fd_);
		}
		return listen_fd_;
	}
}