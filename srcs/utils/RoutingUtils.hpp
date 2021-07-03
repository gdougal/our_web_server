#pragma once
#include <string>
#include "manual_types.h"
class route;
class server_config;

namespace routing_utils {

	Optional_simple<route> get_route(const std::string &url, const server_config &serverConfig);

}// routing_utils
