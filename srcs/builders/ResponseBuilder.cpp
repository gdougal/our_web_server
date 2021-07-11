//
// Created by Lonmouth Mallador on 6/19/21.
//

#include "ResponseBuilder.hpp"
#include "AutoindexResonseBuilder.hpp"
#include "CommonUtils.hpp"
#include "ErrorBuilder.hpp"
#include "Get.hpp"
#include "Head.hpp"
#include "HeadersBuilder.hpp"
#include "ParseUtils.hpp"
#include "Post.hpp"
#include "Put.hpp"
#include "ResponseUtils.hpp"
#include "RoutingUtils.hpp"
#include <map>
#include <repository/ConfigRepository.hpp>

namespace http {

ResponseBuilder::ResponseBuilder(const server_config &serverConfig,
                                 const t_request_data &data)
    : serverConfig(serverConfig), request_data(data) {}

void ResponseBuilder::build_response(std::list<std::vector<uint8_t>> &resp) {

  if (!request_data.request_route.redirect_path.empty())
    return HeadersBuilder::build(R301, connection::CLOSE, "text/plain", 0,
                                 serverConfig.host, serverConfig.port,
                                 request_data.request_route.redirect_path, resp);
  if (request_data.code != SUCCESSFUL &&
      !(request_data.code == ER404 &&
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
    return Post::build(request_data, serverConfig, resp);
  }
  case methods::DELETE: {

    break;
  }
  case methods::LAST_METH:
    break;
  }
  ErrorBuilder::build(ER400, serverConfig, resp);
}

ResponseBuilder::~ResponseBuilder() {}

} // namespace http
