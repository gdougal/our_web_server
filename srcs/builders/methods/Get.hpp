//
// Created by Lonmouth Mallador on 7/4/21.
//

#ifndef WEB_SERVER_GET_HPP
#define WEB_SERVER_GET_HPP

#include "CommonUtils.hpp"
#include "ResponseBuilder.hpp"

class Get {
public:
  static void build_response(const server_config &serverConfig,
                                    const t_request_data &request_datam, std::list<std::vector<uint8_t> >&);
};

#endif // WEB_SERVER_GET_HPP
