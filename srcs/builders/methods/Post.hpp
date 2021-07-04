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
  static std::string  put(const std::string &filename, const t_request_data &data) {
    std::ofstream outfile;
    outfile.open(filename.c_str());
    const std::string content_type(ResponseUtils::get_content_type(filename));
    const bool b_connection = (data.header.find("CONNECTION")->second ==
                               KEEP_ALIVE_STR);

    if (outfile.is_open()) {
      outfile.write(data.body.c_str(), data.body.size());
      return HeadersBuilder::build(ER204,
                                   static_cast<connection>(b_connection),
                                   content_type,
                                   data.body.size());
    }
    else {
      outfile.open(filename.c_str());
      outfile.write(data.body.c_str(), data.body.size());
      return HeadersBuilder::build(R201,
                                   static_cast<connection>(b_connection),
                                   content_type,
                                   data.body.size());
    }
  };

  static std::string  post(const std::string &filename, const t_request_data &data) {};

  virtual ~Post() {};
};


#endif //WEB_SERVER_POST_HPP
