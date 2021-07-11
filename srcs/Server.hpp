//
// Created by Gilberto Dougal on 5/10/21.
//

#ifndef PROXY_SERVER_SERVER_HPP
#define PROXY_SERVER_SERVER_HPP

#include "Client/client.hpp"
#include "fd_creator.hpp"
#include <sys/fcntl.h>
#include "unistd.h"
#include "shared_ptr.hpp"
#include "i_wanna_range_based_for.hpp"
template <typename types, typename protocol_handler = typename types::protocol,
          typename data_type = typename types::datatypes>
class Server {
  struct virtual_server {
    int serv_fd_;
    ft::shared_ptr<data_type> config_data;
    std::list<ft::shared_ptr<Client<types> > > clients_;

    virtual_server(int servFd, const ft::shared_ptr<data_type>& configData)
            : serv_fd_(servFd), config_data(configData) {}

    virtual ~virtual_server() { close(serv_fd_); }
  };
  //local template types
  typedef Client<types>                                  Client_t;
  //local pointers
  typedef ft::shared_ptr<data_type>                      data_ptr;
  typedef ft::shared_ptr<virtual_server>                 v_serv_ptr;
  typedef typename ft::shared_ptr<Client_t>              Client_ptr;
  // local Iterators
  typedef typename std::list<data_ptr>::iterator         iter_data;
  typedef typename std::list<data_ptr>::const_iterator   iter_data_c;
  typedef typename std::list<v_serv_ptr>::iterator       iter_v_serv;
  typedef typename std::list<v_serv_ptr>::const_iterator iter_v_serv_c;
  typedef typename std::list<Client_ptr>::iterator       iter_client;
  typedef typename std::list<Client_ptr>::const_iterator iter_client_c;

public:
  explicit Server(const std::list<data_ptr>& cfg) {
    AUTO_FOR(iter_data_c, data, cfg)
    {
      serv_.push_back(
              new virtual_server( fd_creator::create_listen_socket((*data)->host, (*data)->port), *data )
              );
    }
  };

  virtual ~Server() {
    AUTO_FOR(iter_v_serv, v_serv, serv_) {
      close((*v_serv)->serv_fd_);
    }
  };
  void run_server() throw() {
    int		          ret_select;
    timeval  timeout = {15000, 0};

    while (true) {
      manage_v_server_fd();
      ret_select = select(max_fd_, &read_fds_, &write_fds_, nullptr, &timeout);
      if (!create_client() || ret_select == -1)
        continue;
      manage_client_fd();
      AUTO_FOR(iter_v_serv, v_serv, serv_) {
        iter_client it = (*v_serv)->clients_.begin();
        while (it != (*v_serv)->clients_.end()) {
          if (FD_ISSET((*it)->getFd(), &read_fds_) &&
              (*it)->getCurState() == state::READ_FROM_CLIENT) {
            (*it)->read_from_client();
          }
          if (FD_ISSET((*it)->getFd(), &write_fds_) &&
                     (*it)->getCurState() == state::SEND_TO_CLIENT) {
            (*it)->send_to_client();
          }
          if ((*it)->getCurState() == state::FINALL) {
            if (FD_ISSET((*it)->getFd(), &read_fds_))
              FD_CLR((*it)->getFd(), &read_fds_);
            if (FD_ISSET((*it)->getFd(), &write_fds_))
              FD_CLR((*it)->getFd(), &write_fds_);
            it = (*v_serv)->clients_.erase(it);
          }
          else {
            ++it;
          }
        }
      }
    }
  }

private:
  void manage_v_server_fd() throw() {
    FD_ZERO(&read_fds_);
    FD_ZERO(&write_fds_);
    AUTO_FOR(iter_v_serv, v_serv, serv_) {
      FD_SET((*v_serv)->serv_fd_, &read_fds_);
      if (max_fd_ <= (*v_serv)->serv_fd_)
        max_fd_ = (*v_serv)->serv_fd_ + 1;
    }
  }

  void manage_client_fd() throw() {
    max_fd_ = 0;
    AUTO_FOR(iter_v_serv, v_serv, serv_) {
      AUTO_FOR(iter_client, client, (*v_serv)->clients_) {
        if (!FD_ISSET((*client)->getFd(), &read_fds_)
            && (*client)->getCurState() ==state::READ_FROM_CLIENT) {
          FD_SET((*client)->getFd(), &read_fds_);
        }
        if (!FD_ISSET((*client)->getFd(), &write_fds_)
            && (*client)->getCurState() == state::SEND_TO_CLIENT) {
          FD_SET((*client)->getFd(), &write_fds_);
        }
        max_fd_ = (max_fd_ >= (*client)->getFd() ?
                    max_fd_ : (*client)->getFd()) + 1;
      }
    }
  };

  bool create_client() {
    int client_fd;
    AUTO_FOR(iter_v_serv, v_serv, serv_) {
      if (FD_ISSET((*v_serv)->serv_fd_, &read_fds_) &&
          (client_fd = fd_creator::create_client_fd((*v_serv)->serv_fd_)) > 0) {
        (*v_serv)->clients_.push_back(new Client_t(client_fd, *((*v_serv)->config_data) ) );
      }
      else
        return false;
    }
    return true;
  }
  int max_fd_;
  fd_set read_fds_;
  fd_set write_fds_;
  std::list<v_serv_ptr> serv_;
};

#endif // PROXY_SERVER_SERVER_HPP
