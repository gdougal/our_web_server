//
// Created by Lonmouth Mallador on 7/6/21.
//

#include "Put.hpp"
#include <iostream>
#include "HeadersBuilder.hpp"
#include "ResponseUtils.hpp"
#include "ErrorBuilder.hpp"
#include "CommonUtils.hpp"
#include <fstream>

namespace http {

void Put::build(const t_request_data &data, const server_config &serverConfig,
                std::list<std::vector<uint8_t>> &resp) {
  std::cout << " Here is " << std::endl;

  std::string filename = get_file_name(data.path, serverConfig, resp);
  if (filename.empty())
    return;
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

std::string Put::get_file_name(std::string path,
                               const server_config &serverConfig,
                               std::list<std::vector<uint8_t>> &resp) {
  req_file_status status = is_directory(path);
  if (status == IS_DIRECTORY) {
    ErrorBuilder::build(ER403, serverConfig, resp);
    return "";
  }
  return path.substr(path.find_last_of("/\\") + 1);
}

}