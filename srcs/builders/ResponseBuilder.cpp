//
// Created by Lonmouth Mallador on 6/19/21.
//

#include "ResponseBuilder.hpp"
#include "CommonUtils.hpp"
#include "RoutingUtils.hpp"

ResponseBuilder::ResponseBuilder(const server_config &serverConfig,
                                 const t_request_data &data)
    : serverConfig(serverConfig), request_data(data) {}

void ResponseBuilder::build_response(methods qurey_type, std::list<std::vector<uint8_t> >& resp) {

  if (request_data.code != SUCCESSFUL)
    return ErrorBuilder::build(request_data.code, serverConfig, resp);
  switch (qurey_type) {
  case methods::GET:
    return Get::build_response(serverConfig, request_data, resp);
  case methods::HEAD:
    return Head::build_response(serverConfig, request_data, resp);
  case methods::PUT: {
    return Put::build("test_file.txt", request_data, serverConfig, resp);
  }
  case methods::POST: {
    return Put::build("test_file.txt", request_data, serverConfig, resp);
  }
  case methods::DELETE: {

    break;
  }
  }
  ErrorBuilder::build(ER400, serverConfig, resp);
}

ResponseBuilder::~ResponseBuilder() {}
