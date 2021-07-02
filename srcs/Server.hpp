//
// Created by Gilberto Dougal on 5/10/21.
//

#ifndef PROXY_SERVER_SERVER_HPP
#define PROXY_SERVER_SERVER_HPP

#include "ConfigParser.hpp"
#include "Client/client.hpp"
#include "fd_creator.hpp"
#include <list>

#include "memory"

template <typename types, typename protocol_handler = typename types::protocol,
          typename data_type = typename types::datatypes>
class Server {
public:
  explicit Server(const std::list< std::shared_ptr<data_type> >& cfg) {
    for (auto &item : cfg) {
      serv_.emplace_back(std::make_shared<virtual_server>(
          fd_creator::create_listen_socket(item->host, item->port), item));
    }
    logfile_ = open("logfile.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (logfile_ < 0)
      throw std::runtime_error("Can't create file");
  };

  virtual ~Server() {
    for (auto &v_serv : serv_) {
      close(v_serv->serv_fd_);
    }
    close(logfile_);
  };
  [[noreturn]] void run_server() {
    while (true) {
      manage_client_fd();
      select(max_fd_ + 1, &read_fds_, &write_fds_, nullptr, nullptr);
      create_client();
      for (auto &v_serv : serv_) {
        auto it = v_serv->clients_.begin();
        while (it != v_serv->clients_.end()) {
          if (FD_ISSET((*it)->getFd(), &read_fds_) &&
              (*it)->getCurState() == state::READ_FROM_CLIENT) {
            (*it)->read_from_client();
          } else if (FD_ISSET((*it)->getFd(), &write_fds_) &&
                     (*it)->getCurState() == state::SEND_TO_CLIENT) {
            (*it)->send_to_client(*(v_serv->config_data));
          }
          if ((*it)->getCurState() == state::FINALL) {
            it = v_serv->clients_.erase(it);
          } else {
            ++it;
          }
        }
      }
    }
  }

private:
  void manage_client_fd() {
    FD_ZERO(&read_fds_);
    FD_ZERO(&write_fds_);
    max_fd_ = 0;
    for (auto &v_serv : serv_) {
      FD_SET(v_serv->serv_fd_, &read_fds_);
      if (max_fd_ < v_serv->serv_fd_)
        max_fd_ = v_serv->serv_fd_;
      for (auto &item : v_serv->clients_) {
        if (item->getCurState() == state::READ_FROM_CLIENT)
          FD_SET(item->getFd(), &read_fds_);
        if (item->getCurState() == state::SEND_TO_CLIENT)
          FD_SET(item->getFd(), &write_fds_);
        max_fd_ = max_fd_ > item->getFd() ? max_fd_ : item->getFd();
      }
    }
  };

  void create_client() {
    int client_fd;
    for (auto &v_serv : serv_) {
      if (FD_ISSET(v_serv->serv_fd_, &read_fds_) &&
          (client_fd = fd_creator::create_client_fd(v_serv->serv_fd_)) > 0) {
        v_serv->clients_.emplace_back(std::make_shared<Client<types> >(client_fd, logfile_));
      }
    }
  }
  struct virtual_server {
    int serv_fd_;
    std::shared_ptr<data_type> config_data;
    std::list<std::shared_ptr<Client<types> > > clients_;

    virtual_server(int servFd, const std::shared_ptr<data_type>& configData)
        : serv_fd_(servFd), config_data(configData) {}

    virtual ~virtual_server() { close(serv_fd_); }
  };
  int max_fd_;
  fd_set read_fds_;
  fd_set write_fds_;
  std::list<std::shared_ptr<virtual_server>> serv_;
  int logfile_;
};

#endif // PROXY_SERVER_SERVER_HPP
