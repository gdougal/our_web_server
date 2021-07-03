//
// Created by Gilberto Dougal on 6/29/21.
//

#ifndef WEB_SERVER_REQUEST_DATA_HPP
#define WEB_SERVER_REQUEST_DATA_HPP

#include <map>
#include <string>

class route;

typedef struct request_data {
	const http::map_str&	header;
	const std::string&		body;
	const route&					request_route;
	const std::string&		path;
}							t_request_data;

#endif //WEB_SERVER_REQUEST_DATA_HPP
