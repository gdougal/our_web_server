//
// Created by Lonmouth Mallador on 7/6/21.
//

#pragma once

#include "ResponseBuilder.hpp"

namespace http {

class Put {
private:
  static std::string get_file_name(std::string path, connection con,
                                   const server_config &serverConfig,
                                   std::list<std::vector<uint8_t>> &);

public:
  static connection build(const t_request_data &data,
                          const server_config &serverConfig,
                          std::list<std::vector<uint8_t>> &);
};

} // namespace http