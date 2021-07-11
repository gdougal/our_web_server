//
// Created by Lonmouth Mallador on 7/6/21.
//

#include "Delete.hpp"
#include "CommonUtils.hpp"
#include "HeadersBuilder.hpp"

void http::Delete::build_response(const http::server_config &serverConfig,
                                  const http::t_request_data &request_data,
                                  std::list<std::vector<uint8_t>> &resp) {
  std::remove((serverConfig.path_to_root + request_data.path).c_str());
  HeadersBuilder::build(R204, connection::KEEP_ALIVE, "", 0, serverConfig.host,
                        serverConfig.port, "", resp);
}
