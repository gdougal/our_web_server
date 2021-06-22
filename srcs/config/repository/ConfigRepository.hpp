//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_CONFIGREPOSITORY_HPP
#define WEB_SERVER_CONFIGREPOSITORY_HPP

#include "RouteEntity.hpp"
#include "list"
#include <string>

using namespace std;

struct server_config {
  string host = "127.0.0.1";
  string port = "8080";
  string server_name = "default_name";
  size_t client_body_size;
  list<pair<int, string>> error_pages_paths;
  std::list<route> routes;

  server_config(const string &host, const string &port,
                const string &serverName, size_t client_body_size,
                list<pair<int, string>> &errorPagesPaths,
                std::list<route> routes)
      : host(host), port(port), server_name(serverName),
        error_pages_paths(errorPagesPaths), routes(routes),
        client_body_size(client_body_size) {}
};

#endif // WEB_SERVER_CONFIGREPOSITORY_HPP
