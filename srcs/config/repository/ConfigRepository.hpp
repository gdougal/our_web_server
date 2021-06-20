//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_CONFIGREPOSITORY_HPP
#define WEB_SERVER_CONFIGREPOSITORY_HPP

#include "RouteEntity.hpp"
#include <string>

using namespace std;

struct server_config {
  string host = "127.0.0.1";
  string port = "8080";
  string server_name = "default_name";
  string error_page_path = "defaut_path";
  route *routes;

  server_config(const string &host, const string &port,
                const string &serverName, const string &errorPagePath,
                route *routes)
      : host(host), port(port), server_name(serverName),
        error_page_path(errorPagePath), routes(routes) {}
};

#endif // WEB_SERVER_CONFIGREPOSITORY_HPP
