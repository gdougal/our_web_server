//
// Created by Gilberto Dougal on 6/29/21.
//

#include "Post.hpp"
#include "CgiExecutor.hpp"
#include "Put.hpp"
#include <iostream>

namespace http {

connection Post::build(const t_request_data &data,
                       const server_config &serverConfig,
                       std::list<std::vector<uint8_t>> &resp) {
  size_t size = data.path.find_last_of('.');
  if (size != std::string::npos && serverConfig.cgi_ext == data.path.substr
                                                           (size)
                                  .c_str())
    return CgiExecutor::build(data, serverConfig, resp);
  else
    return Put::build(data, serverConfig, resp);
}

} // namespace http