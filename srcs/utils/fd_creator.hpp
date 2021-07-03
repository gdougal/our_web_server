//
// Created by Gilberto Dougal on 6/5/21.
//

#pragma once
#include "string"

namespace fd_creator {
	void close_fd_error(std::string except, int listen_fd_);
	int create_listen_socket(const std::string& host, const std::string& port);
	int create_client_fd(int listen_fd);
}
