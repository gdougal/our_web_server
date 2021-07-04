#pragma once
#include "manual_types.h"
#include <string>
class route;
class server_config;

namespace routing_utils {
Optional_simple<route> get_route(std::string &url,
                                 const server_config &serverConfig);
} // namespace routing_utils
