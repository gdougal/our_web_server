//
// Created by Lonmouth Mallador on 7/6/21.
//

#include "Put.hpp"
#include "CommonUtils.hpp"
#include "ErrorBuilder.hpp"
#include "HeadersBuilder.hpp"
#include "ResponseUtils.hpp"
#include <fstream>

namespace http {

connection Put::build(const t_request_data &data,
                      const server_config &serverConfig,
                      std::list<std::vector<uint8_t>> &resp) {

  std::string filename =
      get_file_name(data.path, data.status, serverConfig, resp);
  if (filename.empty())
    return HeadersBuilder::build(R200, data.status, "text/plain", 0,
                                 serverConfig.host, serverConfig.port, "",
                                 resp);
  std::ofstream outfile;
  outfile.open(serverConfig.path_to_root + data.request_route.save_path + "/" +
               filename);
  const std::string content_type(ResponseUtils::get_content_type(filename));

  if (outfile.is_open()) {
    outfile.write(data.body.c_str(), data.body.size());
    outfile.close();
    return HeadersBuilder::build(R201, data.status, content_type, 0,
                                 serverConfig.host, serverConfig.port, "",
                                 resp);
  } else {
    outfile.open(serverConfig.path_to_root + data.request_route.save_path +
                 "/" + filename);
    outfile.write(data.body.c_str(), data.body.size());
    outfile.close();
    return HeadersBuilder::build(R204, data.status, content_type, 0,
                                 serverConfig.host, serverConfig.port, "",
                                 resp);
  }
}

std::string Put::get_file_name(std::string path, connection con,
                               const server_config &serverConfig,
                               std::list<std::vector<uint8_t>> &resp) {
  req_file_status status = is_directory(serverConfig.path_to_root + path);
  if (status == IS_DIRECTORY) {
    ErrorBuilder::build(ER403, con, serverConfig, resp);
    return "";
  }
  return path.substr(path.find_last_of("/\\") + 1);
}

} // namespace http