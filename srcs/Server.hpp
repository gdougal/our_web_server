//
// Created by Gilberto Dougal on 5/10/21.
//

#ifndef PROXY_SERVER_SERVER_HPP
#define PROXY_SERVER_SERVER_HPP

#include "client.hpp"
#include "Config.hpp"
#include "fd_creator.hpp"
#include <list>
#include <netinet/in.h>
#include <string>
#include <sys/fcntl.h>
#include <unistd.h>

class Server {
public:
	Server() = delete;
	Server(const Server&) = delete;
	Server(const Config &cfg);
	virtual ~Server();
	[[noreturn]] void run_server();

private:
	void	manage_client_fd();
	void	create_client();

	int									listen_fd_;
	int									max_fd_;
	fd_set							read_fds_;
	fd_set							write_fds_;
	std::list<std::shared_ptr<Client> >	clients_;
	int									logfile_;
};

#endif //PROXY_SERVER_SERVER_HPP
