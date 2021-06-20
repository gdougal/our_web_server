//
// Created by Gilberto Dougal on 5/10/21.
//

#ifndef PROXY_SERVER_SERVER_HPP
#define PROXY_SERVER_SERVER_HPP

#include "client.hpp"
#include "Config.hpp"
#include "fd_creator.hpp"
#include <list>

#include "memory"

template <typename PROTOCOL_HANDLER>
class Server {
public:
	Server(const Config &cfg) {
		listen_fd_ = fd_creator::create_listen_socket(cfg);
		logfile_ = open(cfg.getSection("LOGS_PATH").getStringVal("file").c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (logfile_ < 0)
			throw std::runtime_error("Can't create file");
	};

	virtual ~Server() {
		close(listen_fd_);
		close(logfile_);
	};
	[[noreturn]] void run_server() {
		while (true) {
			manage_client_fd();
			select(max_fd_ + 1, &read_fds_, &write_fds_, nullptr, nullptr);
			create_client();
			auto it = clients_.begin();
			while (it != clients_.end()) {
				if (FD_ISSET((*it)->getFd(), &read_fds_) && (*it)->getCurState() == state::READ_FROM_CLIENT) {
					(*it)->read_from_client();
				}
				else if (FD_ISSET((*it)->getFd(), &write_fds_) && (*it)->getCurState() == state::SEND_TO_CLIENT) {
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

private:
	void	manage_client_fd() {
		FD_ZERO(&read_fds_);
		FD_ZERO(&write_fds_);
		// TODO: от тут цикл добавлять фд всех серверов
		FD_SET(listen_fd_, &read_fds_);
		max_fd_ = listen_fd_;
		for (auto &item: clients_) {
			if (item->getCurState() == state::READ_FROM_CLIENT)
				FD_SET(item->getFd(), &read_fds_);
			if (item->getCurState() == state::SEND_TO_CLIENT)
				FD_SET(item->getFd(), &write_fds_);
			max_fd_ = max_fd_ > item->getFd() ? max_fd_ : item->getFd();
		}
	};

	void	create_client() {
		int		client_fd;
		//TODO: от тут тоже цикл, можно связать виртуальный сервер и клиентов
		if (FD_ISSET(listen_fd_, &read_fds_) &&
				(client_fd = fd_creator::create_client_fd(listen_fd_)) > 0) {
			clients_.emplace_back(new Client(client_fd, logfile_, new PROTOCOL_HANDLER));
		}
	}

	int																	listen_fd_;
	struct serv_data {
		int fd;
		std::string f1;
		std::string f2;
		std::string f3;
		std::string f4;
	};
	int																	max_fd_;
	fd_set															read_fds_;
	fd_set															write_fds_;
	std::list<std::shared_ptr<Client> >	clients_;
//	std::list<std::pair<serv, std::list<Client> > >
	int																	logfile_;
};

#endif //PROXY_SERVER_SERVER_HPP
