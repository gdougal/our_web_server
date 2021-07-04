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
  std::string response_body;

  if (request_data.code != SUCCESSFUL)
    return ErrorBuilder::build(request_data.code,
                               serverConfig);
    switch (qurey_type) {
    case methods::GET: {
      if (is_directory(request_data.path) &&
          request_data.request_route.autoindex)
        response_body = AutoindexResonseBuilder().build(
            serverConfig, PATH_TO_ROOT + request_data.path, request_data.path);
      else {
        response_body = ResponseUtils::read_from_file(request_data.path);
        if (response_body.empty())
          return ErrorBuilder::build(ER404, serverConfig);
      }
      break;
    }
    case methods::HEAD: {
      response_body = ResponseUtils::read_from_file(request_data.path);
      if (response_body.empty())
        return ErrorBuilder::build(ER404, serverConfig);
      return HeadersBuilder::build(R200, connection(KEEP_ALIVE), content_type(HTML),
                            0);
      break;
    }
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

  return HeadersBuilder::build(R200, connection(KEEP_ALIVE), content_type(HTML),
                               response_body.length()) + response_body;
}

ResponseBuilder::~ResponseBuilder() {}
