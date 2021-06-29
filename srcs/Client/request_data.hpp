//
// Created by Gilberto Dougal on 6/29/21.
//

#ifndef WEB_SERVER_REQUEST_DATA_HPP
#define WEB_SERVER_REQUEST_DATA_HPP

#include "map"
#include "string"


typedef std::map<std::string, std::string> map_str;
typedef std::pair<std::string, std::string> pair_str;

typedef struct request_data {
	const map_str& header;
	const pair_str& path;
	const std::string& body;
}							t_request_data;

#endif //WEB_SERVER_REQUEST_DATA_HPP
