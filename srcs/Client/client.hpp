//
// Created by Gilberto Dougal on 5/10/21.
//

#ifndef PROXY_SERVER_BRIDGE_HPP
#define PROXY_SERVER_BRIDGE_HPP

#include "Client/concrete_client_handler/Handler.hpp"
#include "cstring"
#include <netinet/in.h>
#include "ConfigRepository.hpp"

#define PORTION_SIZE 65000

enum state { READ_FROM_CLIENT, SEND_TO_CLIENT, FINALL };

template <typename types, typename protocol_handler = typename types::protocol, typename data_type = typename types::datatypes>
class Client {
	enum state										cur_state_;
	int														fd_;
	std::string										buffer_;
	BaseClientHandler<data_type>*	handler_;
	int														outfile_;
	char*													g_recv_buffer;
public:
	Client(int client_fd, int file, const data_type& data)  :
					fd_(client_fd),
					outfile_(file) {
		cur_state_ = state::READ_FROM_CLIENT;
		handler_ = new protocol_handler(data);
		g_recv_buffer = new char[PORTION_SIZE + 1];
	}
  virtual ~Client() {
		close(fd_);
		delete handler_;
	};
  int getFd() const { return fd_; };
  enum state getCurState() const { return cur_state_; };

  void read_from_client() {
		bzero(g_recv_buffer, PORTION_SIZE + 1);
		static size_t buffer_len;
		buffer_len = recv(fd_, g_recv_buffer, PORTION_SIZE, 0);
		if (buffer_len <= 0 || buffer_len > PORTION_SIZE) {
			cur_state_ = state::FINALL;
			return;
		}
		buffer_.append(g_recv_buffer);
		if ( handler_->is_recvest_end(buffer_) ) {
			if ( handler_->query_parsing(buffer_) ) {
				handler_->logger(buffer_, outfile_);
				cur_state_ = state::SEND_TO_CLIENT;
			}
		}
	}
  void	send_to_client() {
		std::string http(handler_->create_response());
		buffer_.clear();
		if (send(fd_, http.c_str(), http.size(), 0)/*;*/ <= 0) {
			cur_state_ = state::FINALL;
			return ;
		}
		cur_state_ = state::READ_FROM_CLIENT;
	}
};

#endif // PROXY_SERVER_BRIDGE_HPP
