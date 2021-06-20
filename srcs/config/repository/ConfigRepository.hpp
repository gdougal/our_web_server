//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_CONFIGREPOSITORY_HPP
#define WEB_SERVER_CONFIGREPOSITORY_HPP

#include "RouteEntity.hpp"
#include <string>
#include "list"

using namespace std;

struct server_config {
  string host = "127.0.0.1";
  string port = "8080";
  string server_name = "default_name";
  size_t client_body_size;
  string error_page_path = "defaut_path";
  std::list<route> routes;

  server_config(const string &host, const string &port,
                const string &serverName, size_t client_body_size, const string
                                              &errorPagePath,
                std::list<route> routes)
      : host(host), port(port), server_name(serverName),
        error_page_path(errorPagePath), routes(routes), client_body_size(client_body_size) {}
};

#endif // WEB_SERVER_CONFIGREPOSITORY_HPP
