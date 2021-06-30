//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_ROUTEENTITY_HPP
#define WEB_SERVER_ROUTEENTITY_HPP

#include "list"
#include <string>

enum methods { GET, POST, DELETE, HEAD, };

struct route {
		std::string location;
		std::string directory;
		std::string index_file;
		std::string redirect_path;
		std::string cgi_path;
		bool autoindex;
		std::list<methods> methods_allowed;

		route() {}
		route(const route& route) {
			if(this != &route) {
				*this = route;
			}
		}
		route& operator=(const route& route) {
			this->location = route.location;
			this->directory = route.directory;
			this->index_file = route.index_file;
			this->redirect_path = route.redirect_path;
			this->cgi_path = route.cgi_path;
			this->autoindex = route.autoindex;
			this->methods_allowed = route.methods_allowed;
		}
		~route() {}
};

#endif // WEB_SERVER_ROUTEENTITY_HPP
