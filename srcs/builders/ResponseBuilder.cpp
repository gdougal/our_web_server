//
// Created by Lonmouth Mallador on 6/19/21.
//

#include "ResponseBuilder.hpp"
#include "CommonUtils.hpp"
#include "RoutingUtils.hpp"

ResponseBuilder::ResponseBuilder(const server_config &serverConfig,
                                 const t_request_data &data)
    : serverConfig(serverConfig), request_data(data) {}

void ResponseBuilder::build_response(std::list<std::vector<uint8_t> >& resp) {

  if (request_data.code != SUCCESSFUL && !(request_data.code == ER404 &&
                                          (request_data.cur_method == methods::POST ||
                                                  request_data.cur_method == methods::PUT)))
    return ErrorBuilder::build(request_data.code, serverConfig, resp);
  switch (request_data.cur_method) {
  case methods::GET:
    return Get::build_response(serverConfig, request_data, resp);
  case methods::HEAD:
    return Head::build_response(serverConfig, request_data, resp);
  case methods::PUT: {
    return Put::build(request_data, serverConfig, resp);
  }
  case methods::POST: {
    return Put::build(request_data, serverConfig, resp);
  }
  case methods::DELETE: {

    break;
  }
  }
  ErrorBuilder::build(ER400, serverConfig, resp);
}

ResponseBuilder::~ResponseBuilder() {}
