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
  bool search_file(methods qurey_type);
  string build_error(int error_code);
  string build_headers();
  bool get_route();
  list<string> getDirectoryList(string src);
public:
  ResponseBuilder(const server_config &serverConfig, map<string, string>
      headers,
                  pair<string, string> path);
  string build_response(methods qurey_type);
};

#endif // WEB_SERVER_RESPONSEBUILDER_HPP
