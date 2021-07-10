//
// Created by Gilberto Dougal on 6/29/21.
//

#include "Post.hpp"
#include "CgiExecutor.hpp"

namespace http {

  void Post::build(const t_request_data &data,
                  const server_config &serverConfig,
                  std::list<std::vector<uint8_t>> &resp) {
    CgiExecutor::build(data, serverConfig, resp);
  }

}