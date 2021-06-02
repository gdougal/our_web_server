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
#define PORTION_SIZE	10000

enum state {
	READ_FROM_CLIENT,
	SEND_TO_CLIENT,
	FINALL
};

class Client {
	enum state				cur_state_;
	int						fd_;
	int						outfile_;
	std::vector<char>		bufer_;
	size_t					buf_len_;
	std::function<void()>	handler_;
	std::shared_ptr<char> 	tmp_;
public:
	Client(int client_to_proxy, int file);
	virtual ~Client();
	void				caller(bool a);
	int					getFd()	const;
	enum state			getCurState()		const;

private:

	void	send_to_db();
	void	read_from_client();
	void	send_to_client();
	void	read_from_db();
	uint	package_len();
	void	logger();
};



#endif //PROXY_SERVER_BRIDGE_HPP
