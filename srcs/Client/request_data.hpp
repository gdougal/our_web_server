//
// Created by Gilberto Dougal on 6/29/21.
//

#ifndef WEB_SERVER_REQUEST_DATA_HPP
#define WEB_SERVER_REQUEST_DATA_HPP

#include "map"
#include "string"
#include "manual_types.h"

typedef struct request_data {
	http::map_str&	header;
	std::string&		body;
	route&					request_route;
	std::string&		path;
}							t_request_data;

#endif //WEB_SERVER_REQUEST_DATA_HPP
