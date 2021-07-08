#pragma once
#include "manual_types.h"
#include <string>
#include "optional.hpp"
class route;
class server_config;

namespace routing_utils {
ft::optional<route> get_route(std::string &url,
                                 const server_config &serverConfig);
} // namespace routing_utils
