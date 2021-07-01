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

  server_config() {}
  server_config(const string host, const string port,
                const string serverName, size_t client_body_size,
                map<int, string> errorPagesPaths,
                std::list<route> routes)
      : host(host), port(port), server_name(serverName),
        error_pages_paths(errorPagesPaths), routes(routes),
        client_body_size(client_body_size) {}
  server_config(const server_config&  config) {
    if (this != &config)
      *this = config;
  }
  server_config& operator=(const server_config&  config) {
    this->host = config.host;
    this->port = config.port;
    this->server_name = config.server_name;
    this->client_body_size = config.client_body_size;
    this->error_pages_paths = config.error_pages_paths;
    this->routes = config.routes;
    return *this;
  }
  ~server_config() {}
};

#endif // WEB_SERVER_CONFIGREPOSITORY_HPP