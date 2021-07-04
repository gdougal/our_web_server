//
// Created by Lonmouth Mallador on 6/19/21.
//

#include "ResponseBuilder.hpp"
#include "CommonUtils.hpp"
#include "RoutingUtils.hpp"

ResponseBuilder::ResponseBuilder(const server_config &serverConfig,
                                 const t_request_data &data)
    : serverConfig(serverConfig), request_data(data) {}

string ResponseBuilder::build_response(methods qurey_type) {

  if (request_data.code != SUCCESSFUL)
    return ErrorBuilder::build(request_data.code, serverConfig);
  switch (qurey_type) {
  case methods::GET:
    return Get::build_response(serverConfig, request_data);
  case methods::HEAD:
    return Head::build_response(serverConfig, request_data);
  case methods::PUT: {
    break;
  }
  case methods::POST: {

    break;
  }
  case methods::DELETE: {

    break;
  }
  }
  return ErrorBuilder::build(ER400, serverConfig);
}

ResponseBuilder::~ResponseBuilder() {}
