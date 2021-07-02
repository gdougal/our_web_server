//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_CONFIGREPOSITORY_HPP
#define WEB_SERVER_CONFIGREPOSITORY_HPP

#include "RouteEntity.hpp"
#include "list"
#include <string>
#include <memory>


enum connection {KEEP_ALIVE, CLOSE};
enum content_type { HTML, CSS, JS, JPEG, PNG, BMP, UNDEFINED };

struct server_config {
  std::string	host;
  std::string	port;
  std::string	server_name;
  std::string	cgi_ext;
	std::string	cgi_path;
  std::map<int, std::string> error_pages_paths;
  std::list<std::shared_ptr<route> > routes; // TODO: сделать на указателях

  server_config() {}
  server_config(std::map<std::string, ConfigParser::Section>& data):
					host(data["server"].getStrValue("host")),
					port(data["server"].getStrValue("port")),
					server_name(data["server"].getStrValue("server_name")),
					cgi_ext(data["server"].getStrValue("cgi_ext")),
					cgi_path(data["server"].getStrValue("cgi_path"))
	{
  	if (data.find("error_pages") != data.end()) {
			for (std::map<std::string, OptStr>::iterator iter = data["error_pages"].getBeginSectIter();
					 iter != data["error_pages"].getEndSectIter(); ++iter) {
				error_pages_paths.insert(std::make_pair(std::stoi(iter->first),
																								iter->second.get_or("")));
			}
		}
  	for (int idx = 0; idx < data["routes"].getContentSize(); ++idx) {
			routes.emplace_back(std::make_shared<route>(data["routes"], idx ));
  	}
  }
  server_config(const server_config&  config)
  {
		if (this != &config)
			*this = config;
  };

  server_config& operator=(const server_config&  config) {
		this->host = config.host;
		this->port = config.port;
		this->server_name = config.server_name;
		this->cgi_ext = config.cgi_ext;
		this->cgi_path = config.cgi_path;
		this->error_pages_paths = config.error_pages_paths;
		this->routes = config.routes;
		return *this;
  };
	server_config(server_config&&  config) = default;

  ~server_config() {}
};

#endif // WEB_SERVER_CONFIGREPOSITORY_HPP