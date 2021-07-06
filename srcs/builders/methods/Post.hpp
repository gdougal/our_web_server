//
// Created by Gilberto Dougal on 6/29/21.
//

#ifndef WEB_SERVER_POST_HPP
#define WEB_SERVER_POST_HPP

#include "ResponseBuilder.hpp"
#include "fstream"

class Post {
private:
  Post() = delete;

  Post(const Post &ref) = delete;

  Post &operator=(const Post &ref) = delete;

public:
  static void post(const std::string &filename, const t_request_data &data,
                   const server_config &serverConfig,
                   std::list<std::vector<uint8_t>> &);

  virtual ~Post(){};
};

#endif // WEB_SERVER_POST_HPP
