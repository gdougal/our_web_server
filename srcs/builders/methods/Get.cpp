//
// Created by Lonmouth Mallador on 7/4/21.
//

#include "Get.hpp"
#include <iostream>
#include "unistd.h"

std::string Get::build_response(const server_config &serverConfig,
                                const t_request_data &request_data) {
  std::string response_body;
  std::string content_type = ".html";
  if (is_directory(request_data.path) && request_data.request_route.autoindex)
    response_body = AutoindexResonseBuilder().build(
        serverConfig, PATH_TO_ROOT + request_data.path, request_data.path);
  else {
    response_body = ResponseUtils::read_from_file(request_data.path);
    content_type = ResponseUtils::get_content_type(request_data.path);
    if (response_body.empty())
      return ErrorBuilder::build(ER404, serverConfig);
  }
  write(1, response_body.c_str(), response_body.size());
  return HeadersBuilder::build(R200, connection(KEEP_ALIVE), content_type,
                               response_body.size()) +
         response_body;
}