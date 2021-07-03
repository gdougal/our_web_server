//
// Created by Gilberto Dougal on 6/29/21.
//

#pragma once
#include <map>
#include <string>

class route;

typedef struct request_data {
	const http::map_str&	header;
	const std::string&		body;
	const route&					request_route;
	const std::string&		path;
	const handl_ret_codes code;
}							t_request_data;

