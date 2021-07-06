//
// Created by Lonmouth Mallador on 7/4/21.
//

#include "Head.hpp"

void Head::build_response(const server_config &serverConfig,
                                 const t_request_data &request_data, std::list<std::vector<uint8_t> >& resp) {

  ResponseUtils::read_from_file(request_data.path, resp);
  if ((*resp.begin()).empty())
    ErrorBuilder::build(ER404, serverConfig, resp);
  HeadersBuilder::build(
      R200, connection(KEEP_ALIVE),
      ResponseUtils::get_content_type(request_data.path), 0, serverConfig.host,
                                                             resp);
}
