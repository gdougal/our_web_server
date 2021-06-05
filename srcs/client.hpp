//
// Created by Gilberto Dougal on 5/10/21.
//

#ifndef PROXY_SERVER_BRIDGE_HPP
#define PROXY_SERVER_BRIDGE_HPP

#include <iostream>
#include <list>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <vector>
#include <functional>
#include <memory>
#include <map>

#define PORTION_SIZE  65000

enum state {
	READ_FROM_CLIENT,
	SEND_TO_CLIENT,
	FINALL
};

class Client {
	enum state	cur_state_;
	int					fd_;
	int					outfile_;
	std::string	bufer_;
	size_t			buf_len_;
	char*				tmp_;
	std::map<std::string, std::string>	query_;

public:
	Client(int client_to_proxy, int file);
	virtual	~Client();
	int			getFd() const;
	enum		state getCurState() const;
	void		read_from_client();
	void		send_to_client();
private:
	void logger();
};


#endif //PROXY_SERVER_BRIDGE_HPP
