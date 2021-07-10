//
// Created by Lonmouth Mallador on 7/6/21.
//

#ifndef WEB_SERVER_CGIEXECUTOR_HPP
#define WEB_SERVER_CGIEXECUTOR_HPP

#include "ResponseBuilder.hpp"

namespace http {
class CgiExecutor {
private:
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

#endif // WEB_SERVER_CGIEXECUTOR_HPP
