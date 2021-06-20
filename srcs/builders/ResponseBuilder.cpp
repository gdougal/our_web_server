//
// Created by Lonmouth Mallador on 6/19/21.
//

#include "ResponseBuilder.hpp"
#include <http_stuff.hpp>

string ResponseBuilder::build_response() {
  if (!check_request_valid())
    return build_error();
  std::ifstream page("/goinfre/lmallado/our_web_server" + path.second);
  std::string body;
  std::string tmp;
  while (std::getline(page, tmp)) {
    body += tmp;
  };
  return http::request_init + std::to_string(body.length()) +
             http::query_end + body;
}



string ResponseBuilder::build_error() {

  return std::string();
}

bool ResponseBuilder::check_request_valid() {

  return true;
}

ResponseBuilder::ResponseBuilder(server_config &serverConfig,
                                 map<string, string> headers,
                                 pair<string, string> path)
    : serverConfig(serverConfig), headers(headers), path(path) {

}
string ResponseBuilder::build_headers() {


  return std::string();
}
