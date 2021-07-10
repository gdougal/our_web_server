//
// Created by Lonmouth Mallador on 7/6/21.
//
#pragma once
#include "ResponseBuilder.hpp"

namespace http {
class CgiExecutor {
private:
  static size_t cnt_;
  static std::list<std::string> init_env(const t_request_data &data,
                                  const server_config &serverConfig);
  static char **get_env(const t_request_data &data, const server_config
                                                  &serverConfig);

public:
  static void build(const t_request_data &data,
                    const server_config &serverConfig,
                    std::list<std::vector<uint8_t>> &);
};

} // namespace http

