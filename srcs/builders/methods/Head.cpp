//
// Created by Lonmouth Mallador on 7/4/21.
//

#include "Head.hpp"

std::string Head::build_response(const server_config &serverConfig,
                                 const t_request_data &request_data) {
  std::string response_body;

  response_body = ResponseUtils::read_from_file(request_data.path);
  if (response_body.empty())
    return ErrorBuilder::build(ER404, serverConfig);
  return HeadersBuilder::build(
      R200, connection(KEEP_ALIVE),
      ResponseUtils::get_content_type(request_data.path), 0);
}
