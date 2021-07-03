//
// Created by Lonmouth Mallador on 6/19/21.
//
#pragma once
#include <map>

#include "config/Parser/ConfigParser.hpp"




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
  explicit route(const ConfigParser::Section& ref, int idx);
  route(const route &route);
  route &operator=(const route &route);
	route(route &&route) = default;
  ~route() {}
};

