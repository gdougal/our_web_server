//
// Created by Gilberto Dougal on 6/29/21.
//

#include "Post.hpp"
#include "Put.hpp"
#include "CgiExecutor.hpp"

namespace http {

  connection Post::build(const t_request_data &data,
                  const server_config &serverConfig,
                  std::list<std::vector<uint8_t>> &resp) {
   // if (serverConfig.cgi_ext == data.path.substr(data.path.find_last_of('.')))
   return CgiExecutor::build(data, serverConfig, resp);
//    else
//      Put::build(data, serverConfig, resp);
  }

}