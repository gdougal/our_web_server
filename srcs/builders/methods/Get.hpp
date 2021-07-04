//
// Created by Lonmouth Mallador on 7/4/21.
//

#ifndef WEB_SERVER_GET_HPP
#define WEB_SERVER_GET_HPP

#include "CommonUtils.hpp"
#include "ResponseBuilder.hpp"

class Get {
public:
  static std::string build_response(const server_config &serverConfig,
                                    const t_request_data &request_data);
};

#endif // WEB_SERVER_GET_HPP
