//
// Created by Lonmouth Mallador on 7/4/21.
//

#include "Get.hpp"
#include <iostream>

void Get::build_response(const server_config &serverConfig,
                                const t_request_data &request_data, std::list<std::vector<uint8_t> >& resp) {
  std::string content_type = ".html";
  if (is_directory(request_data.path) && request_data.request_route.autoindex) {
    AutoindexResonseBuilder().build(
            serverConfig, PATH_TO_ROOT + request_data.path, request_data.path,
            resp);
  }
  else {
    ResponseUtils::read_from_file(request_data.path, resp);
    content_type = ResponseUtils::get_content_type(request_data.path);
    if (resp.empty())
      ErrorBuilder::build(ER404, serverConfig, resp);
  }
  HeadersBuilder::build(R200, connection(KEEP_ALIVE), content_type,
                               (*resp.begin()).size(), serverConfig.host, resp);
  std::string end_str = parse_utils::query_end;
  resp.emplace_back(std::vector<uint8_t>(end_str.begin(), end_str.end()));
}