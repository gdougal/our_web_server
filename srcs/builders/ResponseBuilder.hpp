//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_RESPONSEBUILDER_HPP
#define WEB_SERVER_RESPONSEBUILDER_HPP

#include "ConfigRepository.hpp"
#include <map>
#include <repository/ConfigRepository.hpp>

using namespace std;

class ResponseBuilder {

private:
  server_config serverConfig;
  map<string, string> &headers;
  pair<string, string> path;
  bool check_request_valid();
  string build_error();
  string build_headers();

public:
  ResponseBuilder(server_config &serverConfig, map<string, string> headers,
                  pair<string, string> path);
  string build_response();
};

#endif // WEB_SERVER_RESPONSEBUILDER_HPP
