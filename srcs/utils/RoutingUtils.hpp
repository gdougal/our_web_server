#pragma once
#include "manual_types.h"
#include <string>
#include "optional.hpp"
class server_config;

namespace http {
class route;

  namespace routing_utils {
    ft::optional<route> get_route(std::string &url,
                                  const server_config &serverConfig);
  } // namespace routing_utils

} // namespace http