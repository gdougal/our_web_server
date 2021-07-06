//
// Created by Lonmouth Mallador on 6/30/21.
//

#include "ErrorBuilder.hpp"
#include <HeadersBuilder.hpp>
#include <iostream>

void ErrorBuilder::build(handl_ret_codes error_code, server_config serverConfig,
                         std::list<std::vector<uint8_t> > &resp) {
  std::map<int, std::string>::iterator it =
          serverConfig.error_pages_paths.find(error_code);
  std::string path_to_error_page = "";
  if (it == serverConfig.error_pages_paths.end()) {
    path_to_error_page = default_error_pages.find(error_code)->second;
  }
  else {
    path_to_error_page = it->second;
  }
  ResponseUtils::read_from_file(path_to_error_page, resp);
  return HeadersBuilder::build(error_code, connection(CLOSE),
                               ResponseUtils::get_content_type(".html"),
                               (*resp.begin()).size(), serverConfig.host, resp);
}
