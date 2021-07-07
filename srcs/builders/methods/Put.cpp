//
// Created by Lonmouth Mallador on 7/6/21.
//

#include "Put.hpp"

void Put::build(const std::string &filename, const t_request_data &data,
                const server_config &serverConfig,
                std::list<std::vector<uint8_t>> &resp) {
  std::ofstream outfile;
  outfile.open(filename.c_str());
  const std::string content_type(ResponseUtils::get_content_type(filename));
  const bool b_connection =
      (data.header.find("CONNECTION")->second == KEEP_ALIVE_STR);

  if (outfile.is_open()) {
    outfile.write(data.body.c_str(), data.body.size());
    HeadersBuilder::build(R201, static_cast<connection>(b_connection),
                          content_type, data.body.size(), serverConfig.host,
                          resp);
  } else {
    outfile.open(filename.c_str());
    outfile.write(data.body.c_str(), data.body.size());
    HeadersBuilder::build(ER204, static_cast<connection>(b_connection),
                          content_type, data.body.size(), serverConfig.host,
                          resp);
  }
}
