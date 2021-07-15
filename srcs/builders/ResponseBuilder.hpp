//
// Created by Lonmouth Mallador on 6/19/21.
//
#pragma once

#include "Client/request_data.hpp"
#include "ConfigRepository.hpp"
#include "vector"

namespace http {
  class ResponseBuilder {

  private:
    server_config serverConfig;

    const t_request_data &request_data;

  public:
    ResponseBuilder(const server_config &serverConfig,
                    const t_request_data &data);

    connection build_response(std::list<std::vector<uint8_t> > &);

    virtual ~ResponseBuilder();
  };
}