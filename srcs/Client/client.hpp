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
#include "iostream"
#define PORTION_SIZE 60000

enum state { READ_FROM_CLIENT, SEND_TO_CLIENT, FINALL };

template <typename types, typename protocol_handler = typename types::protocol,
          typename data_type = typename types::datatypes,
          typename handle_status = typename types::ret_codes>
class Client {
  typedef ft::shared_ptr<BaseClientHandler<data_type, handle_status> > Handler;
  typedef ft::shared_ptr<char> char_arr;
  typedef std::list<std::vector<uint8_t>> t_resp;

  enum state cur_state_;
  int fd_;
  std::string buffer_;
  Handler handler_;
  t_resp  resp_;
  size_t cur_pos_;
  char_arr g_recv_buffer;
  bool     client_final_status_;

public:
  Client(int client_fd, const data_type &data)
      : fd_(client_fd),
      g_recv_buffer(new char[PORTION_SIZE + 1])
      {
    cur_pos_ = 0;
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
    int buffer_len;
    buffer_len = recv(fd_, &(*g_recv_buffer), PORTION_SIZE, 0);
    if (buffer_len < 0) {
      cur_state_ = FINALL;
      return;
    }
    else if(buffer_len == 0)
      return;
    buffer_.insert(buffer_.end(), &(*g_recv_buffer), &(*g_recv_buffer) + buffer_len);
    if (handler_->is_recvest_end(buffer_)) {
      if (handler_->query_parsing(buffer_) != handle_status::CONTINUE) {
        buffer_.clear();
        cur_state_ = SEND_TO_CLIENT;
      }
    }
  }

  void send_to_client() {
    if (resp_.empty()) {
      client_final_status_ = handler_->create_response(resp_);
    }
    if ( !resp_.empty() ) {
      int tmp = send(fd_, &(resp_.begin()->data()[cur_pos_]),
                 resp_.begin()->size() - cur_pos_, 0);
      cur_pos_ += tmp;
      if (cur_pos_ == (resp_.begin())->size()) {
        cur_pos_ = 0;
        resp_.pop_front();
        if (resp_.empty()) {
          if (client_final_status_)
            cur_state_ = READ_FROM_CLIENT;
          else
            cur_state_ = FINALL;
        }
      }
    }
  }
};
