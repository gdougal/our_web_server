//
// Created by Lonmouth Mallador on 7/4/21.
//

#ifndef WEB_SERVER_HEAD_HPP
#define WEB_SERVER_HEAD_HPP

#include "ResponseBuilder.hpp"

namespace http {

  class Head {
  public:
    static connection build_response(const server_config &serverConfig,
                               const t_request_data &request_data,
                               std::list<std::vector<uint8_t> > &resp);
  };

}
#endif // WEB_SERVER_HEAD_HPP
