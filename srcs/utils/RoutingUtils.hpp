#pragma once
#include <string>
class route;
class server_config;

namespace routing_utils {

	route *get_route(const std::string &url, const server_config &serverConfig);

}// routing_utils
