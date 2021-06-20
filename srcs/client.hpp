//
// Created by Gilberto Dougal on 5/10/21.
//

#ifndef PROXY_SERVER_BRIDGE_HPP
#define PROXY_SERVER_BRIDGE_HPP

#include "Handler.hpp"
#include "cstring"
#include <netinet/in.h>
#include "ConfigRepository.hpp"

#define PORTION_SIZE 65000

enum state { READ_FROM_CLIENT, SEND_TO_CLIENT, FINALL };

class Client {
	enum state						cur_state_;
	int										fd_;
	std::string						buffer_;
	BaseClientHandler*		handler_;
	int										outfile_;
	char*									g_recv_buffer;
public:
  Client(int client_to_proxy, int file, BaseClientHandler *type_client);
  virtual ~Client();
  int getFd() const;
  enum state getCurState() const;
  void read_from_client();
  void send_to_client(const server_config& data);
};

#endif // PROXY_SERVER_BRIDGE_HPP
