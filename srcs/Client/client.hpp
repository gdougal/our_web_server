//
// Created by Gilberto Dougal on 5/10/21.
//

#pragma once
#include "ConfigRepository.hpp"
#include "Handler.hpp"
#include "cstring"
#include <netinet/in.h>
#include <stack>
#include <unistd.h>

#define PORTION_SIZE 65000

enum state { READ_FROM_CLIENT, SEND_TO_CLIENT, FINALL };

template <typename types, typename protocol_handler = typename types::protocol,
          typename data_type = typename types::datatypes,
          typename handle_status = typename types::ret_codes>
class Client {
  typedef ft::shared_ptr<BaseClientHandler<data_type, handle_status> > Handler;
  typedef ft::shared_ptr<char> char_arr;

  enum state cur_state_;
  int fd_;
  std::string buffer_;
  Handler handler_;
  int outfile_;
   char_arr g_recv_buffer;

public:
  Client(int client_fd, int file, const data_type &data)
      : fd_(client_fd),
      outfile_(file),
      g_recv_buffer(new char[PORTION_SIZE + 1])
      {
    cur_state_ = state::READ_FROM_CLIENT;
    handler_ = new protocol_handler(data);
  }
  virtual ~Client() {
    close(fd_);
  };
  int getFd() const { return fd_; };
  enum state getCurState() const { return cur_state_; };

  void read_from_client() {
    bzero(&(*g_recv_buffer), PORTION_SIZE + 1);
    static size_t buffer_len;
    buffer_len = recv(fd_, &(*g_recv_buffer), PORTION_SIZE, 0);
    if (buffer_len <= 0 || buffer_len > PORTION_SIZE) {
      cur_state_ = FINALL;
      return;
    }
    buffer_.insert(buffer_.end(), &(*g_recv_buffer), &(*g_recv_buffer) + buffer_len);
    if (handler_->is_recvest_end(buffer_)) {
      if (handler_->query_parsing(buffer_) != handle_status::CONTINUE) {
        handler_->logger(buffer_, outfile_);
        cur_state_ = SEND_TO_CLIENT;
      }
    }
  }
  void send_to_client() {
    std::list<std::vector<uint8_t>> resp;
    handler_->create_response(resp);
    buffer_.clear();
    for (auto &message : resp) {
      if (send(fd_, message.data(), message.size(), 0) /*;*/ <= 0) {
        cur_state_ = FINALL;
        return;
      }
    }
    cur_state_ = READ_FROM_CLIENT;
  }
};
