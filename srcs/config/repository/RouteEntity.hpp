//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_ROUTEENTITY_HPP
#define WEB_SERVER_ROUTEENTITY_HPP

#include "list"
#include <string>
#include "map"
#include "ParseUtils.hpp"
#include "ConfigParser.hpp"




static const char* enum_str[] = { "GET", "POST", "DELETE", "HEAD", "PUT" };

struct route {
  std::string location;
  std::string directory;
	std::list<std::string> directory_word_list;
  std::string index_file;
  std::string redirect_path;
  std::string save_path;
  int body_size;
  bool autoindex;
  std::list<methods> methods_allowed;

  route() = default;
  explicit route(const ConfigParser::Section& ref, int idx):
				autoindex(false),
      	location( ref.getStrValue("route", idx) ),
      	directory( ref.getStrValue("directory", idx) ), // TODO: разобраться, почему при копировании объекта класса меняется
        index_file(ref.getStrValue("index_file", idx) ),
        redirect_path(ref.getStrValue("redirection", idx) ), // TODO: Какой path
        save_path(ref.getStrValue("save_path", idx) ),
        body_size(std::stoi(ref.getStrValue("limit_body_size", idx, "-1") )) {
		if (ref.getStrValue("autoindex", idx) == "on")
			autoindex = true;
		std::string meth(ref.getStrValue("methods_allowed", idx) );
		for (size_t pos = 0, end ; ; pos = meth.find(';', pos + 1) + 1) {
			end = meth.find(';', pos);
			if (end == std::string::npos)
				end = meth.size();
			auto part = meth.substr(pos, end);
			for (int idx = 0; static_cast<methods>(idx) != methods::LAST_METH ; ++idx) {
				if (enum_str[idx] == part) {
					methods_allowed.push_back(static_cast<methods>(idx));
					break;
				}
			}
			if (end == meth.size())
				break;
		}
    directory_word_list = (parse_utils::getDirectoryList(directory));
  }

  route(const route &route)
  {
  	if (&route != this)
  		*this = route;
  }

  route &operator=(const route &route) {
		this->location = route.location;
		this->directory = route.directory;
		this->index_file = route.index_file;
		this->redirect_path = route.redirect_path;
		this->save_path = route.save_path;
		this->body_size = route.body_size;
		this->autoindex = route.autoindex;
		this->methods_allowed = route.methods_allowed;
		return *this;
  };
	route(route &&route) = default;
  ~route() {}
};

#endif // WEB_SERVER_ROUTEENTITY_HPP
