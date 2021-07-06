//
// Created by Lonmouth Mallador on 7/6/21.
//

#ifndef WEB_SERVER_PUT_HPP
#define WEB_SERVER_PUT_HPP

#include "ResponseBuilder.hpp"

class Put {
public:
  static void build(const std::string &filename, const t_request_data &data,
                    const server_config &serverConfig,
                    std::list<std::vector<uint8_t>> &);
};

#endif // WEB_SERVER_PUT_HPP
