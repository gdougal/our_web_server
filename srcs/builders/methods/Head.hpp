//
// Created by Lonmouth Mallador on 7/4/21.
//

#ifndef WEB_SERVER_HEAD_HPP
#define WEB_SERVER_HEAD_HPP

#include "ResponseBuilder.hpp"

class Head {
public:
  static std::string build_response(const server_config &serverConfig,
                                    const t_request_data &request_data);
};

#endif // WEB_SERVER_HEAD_HPP
