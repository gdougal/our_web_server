//
// Created by Gilberto Dougal on 6/29/21.
//

#pragma once

#include "ResponseBuilder.hpp"
#include "fstream"

namespace http {

  class Post {
  private:
    Post() = delete;

    Post(const Post &ref) = delete;

    Post &operator=(const Post &ref) = delete;

  public:
    static void post(const std::string &filename, const t_request_data &data,
                     const server_config &serverConfig,
                     std::list<std::vector<uint8_t>> &);

    virtual ~Post() {};
  };

}