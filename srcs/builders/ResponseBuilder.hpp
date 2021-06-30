//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_RESPONSEBUILDER_HPP
#define WEB_SERVER_RESPONSEBUILDER_HPP

#include "ConfigRepository.hpp"
#include <map>
#include <repository/ConfigRepository.hpp>
#include "AutoindexResonseBuilder.hpp"
#include "ResponseUtils.hpp"
#include "Client/request_data.hpp"
#include "ErrorBuilder.hpp"
#include "ParseUtils.hpp"
#include "HeadersBuilder.hpp"

using namespace std;

class ResponseBuilder {

private:
  server_config serverConfig;
  string search_file(route *r);
  string build_headers();
  const t_request_data& request_data;
  list<list<string>> server_routes;
  route *get_route();
  list<string> getDirectoryList(string src);
  bool is_method_allowed(methods request_method, route *r);
public:
  ResponseBuilder(const server_config &serverConfig, const t_request_data& data);
  string build_response(methods qurey_type);
  virtual ~ResponseBuilder();

};

#endif // WEB_SERVER_RESPONSEBUILDER_HPP
