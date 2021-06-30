//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_CONFIGREPOSITORY_HPP
#define WEB_SERVER_CONFIGREPOSITORY_HPP

#include "RouteEntity.hpp"
#include "list"
#include <string>
#include "map"

using namespace std;

enum connection {KEEP_ALIVE, CLOSE};
enum content_type { HTML, CSS, JS, JPEG, PNG, BMP, UNDEFINED };

struct server_config {
  string host = "127.0.0.1";
  string port = "8080";
  string server_name = "default_name";
  size_t client_body_size;
  map<int, string> error_pages_paths;
  std::list<route> routes;

  server_config(const string host, const string port,
                const string serverName, size_t client_body_size,
                map<int, string> errorPagesPaths,
                std::list<route> routes)
      : host(host), port(port), server_name(serverName),
        error_pages_paths(errorPagesPaths), routes(routes),
        client_body_size(client_body_size) {}
};

#endif // WEB_SERVER_CONFIGREPOSITORY_HPP
