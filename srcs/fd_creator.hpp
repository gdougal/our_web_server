//
// Created by Gilberto Dougal on 6/5/21.
//

#ifndef WEB_SERVER_FD_CREATOR_HPP
#define WEB_SERVER_FD_CREATOR_HPP

#include "ConfigParser.hpp"
#include <iostream>
#include <sys/fcntl.h>
#include <unistd.h>

namespace fd_creator {
	void close_fd_error(std::string except, int listen_fd_);
	int create_listen_socket(const std::string& host, const std::string& port);
	int create_client_fd(int listen_fd);
}


#endif //WEB_SERVER_FD_CREATOR_HPP
