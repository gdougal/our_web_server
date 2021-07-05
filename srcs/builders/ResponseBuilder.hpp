//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_RESPONSEBUILDER_HPP
#define WEB_SERVER_RESPONSEBUILDER_HPP

#include "AutoindexResonseBuilder.hpp"
#include "Client/request_data.hpp"
#include "ConfigRepository.hpp"
#include "ErrorBuilder.hpp"
#include "HeadersBuilder.hpp"
#include "ParseUtils.hpp"
#include "ResponseUtils.hpp"
#include <map>
#include <repository/ConfigRepository.hpp>
#include "Get.hpp"
#include "Head.hpp"
#include "vector"
class ResponseBuilder {

private:
  server_config serverConfig;

  const t_request_data &request_data;

public:
  ResponseBuilder(const server_config &serverConfig,
                  const t_request_data &data);
  void build_response(methods qurey_type, std::list<std::vector<uint8_t> >&);
  virtual ~ResponseBuilder();
};

#endif // WEB_SERVER_RESPONSEBUILDER_HPP
