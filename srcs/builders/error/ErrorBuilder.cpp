//
// Created by Lonmouth Mallador on 6/30/21.
//

#include "ErrorBuilder.hpp"
#include <HeadersBuilder.hpp>
#include <iostream>

string ErrorBuilder::build(const int &error_code, server_config serverConfig) {
  map<int, string>::iterator it =
      serverConfig.error_pages_paths.find(error_code);
  string path_to_error_page = "";
  if (it == serverConfig.error_pages_paths.end()) {
    path_to_error_page = default_error_pages.find(error_code)->second;
  } else {
    path_to_error_page = it->second;
  }
  string body = ResponseUtils::read_from_file(path_to_error_page);
  return HeadersBuilder::build(error_code, connection(CLOSE),
                               content_type(HTML), body.length()) +
         body;
}
