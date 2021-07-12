//
// Created by Lonmouth Mallador on 7/6/21.
//

#ifndef WEB_SERVER_DELETE_HPP
#define WEB_SERVER_DELETE_HPP

#include "ResponseBuilder.hpp"

namespace http {
  class Delete {
  public:
    static connection build_response(const server_config &serverConfig,
                               const t_request_data &request_data,
                               std::list<std::vector<uint8_t> > &);
  };
}

#endif // WEB_SERVER_DELETE_HPP
