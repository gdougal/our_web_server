//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_CONFIGREPOSITORY_HPP
#define WEB_SERVER_CONFIGREPOSITORY_HPP

#include "RouteEntity.hpp"
#include "list"
#include "map"
#include <string>

using namespace std;

enum connection { KEEP_ALIVE, CLOSE };
enum content_type { HTML, CSS, JS, JPEG, PNG, BMP, UNDEFINED };

struct server_config {
  string host = "127.0.0.1";
  string port = "8080";
  string server_name = "default_name";
  string cgi_ext;
  string cgi_path;
  map<int, string> error_pages_paths;
  std::list<route> routes;

  server_config() {}
  server_config(const string host, const string port, const string serverName,
                map<int, string> errorPagesPaths, std::list<route> routes,
                string cgi_ext, string cgi_path)
      : host(host), port(port), server_name(serverName),
        error_pages_paths(errorPagesPaths), routes(routes), cgi_path(cgi_path),
        cgi_ext(cgi_ext) {}
  server_config(const server_config &config) {
    if (this != &config)
      *this = config;
  }
  server_config &operator=(const server_config &config) {
    this->host = config.host;
    this->port = config.port;
    this->server_name = config.server_name;
    this->error_pages_paths = config.error_pages_paths;
    this->cgi_ext = config.cgi_ext;
    this->cgi_path = config.cgi_path;
    this->routes = config.routes;
    return *this;
  }
  ~server_config() {}
};

#endif // WEB_SERVER_CONFIGREPOSITORY_HPP