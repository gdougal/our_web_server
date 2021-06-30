//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_CONFIGREPOSITORY_HPP
#define WEB_SERVER_CONFIGREPOSITORY_HPP

#include "RouteEntity.hpp"
#include "list"
#include <string>
#include "map"

struct server_config {
  std::string       host;
  std::string       port;
  std::string       server_name;
  size_t            client_body_size;
  std::map<int, std::string>  error_pages_paths;
  std::list<route>  routes;

  server_config() {}
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
  }
  ~server_config() {}
};

#endif // WEB_SERVER_CONFIGREPOSITORY_HPP
