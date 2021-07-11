//
// Created by Lonmouth Mallador on 7/4/21.
//

#pragma once


#include "ResponseBuilder.hpp"


namespace http {

  class Get {
  public:
    static void build_response(const server_config &serverConfig,
                               const t_request_data &request_data,
                               std::list<std::vector<uint8_t> > &);
  };

}
