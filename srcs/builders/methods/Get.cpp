//
// Created by Lonmouth Mallador on 7/4/21.
//

#include "Get.hpp"
#include "AutoindexResonseBuilder.hpp"
#include "CommonUtils.hpp"
#include "ErrorBuilder.hpp"
#include "HeadersBuilder.hpp"
#include "ParseUtils.hpp"
#include "ResponseUtils.hpp"

namespace http {
connection Get::build_response(const server_config &serverConfig,
                               const t_request_data &request_data,
                               std::list<std::vector<uint8_t>> &resp) {
  connection stat;
  std::string content_type = ".html";
  if (is_directory(serverConfig.path_to_root + request_data.path) &&
      request_data.request_route.autoindex) {
    AutoindexResonseBuilder().build(
        serverConfig, serverConfig.path_to_root + request_data.path,
        request_data.path, resp);
  } else {
    ResponseUtils::read_from_file(serverConfig.path_to_root + request_data.path,
                                  resp);
    content_type = ResponseUtils::get_content_type(request_data.path);
    if (resp.empty() || (!resp.empty() && (*resp.begin()).empty())) {
      return ErrorBuilder::build(ER404, request_data.status, serverConfig,
                                 resp);
    }
  }
  map_str::const_iterator it = request_data.header.find("USER-AGENT");
  if (it != request_data.header.end() && it->second == "Go-http-client/1.1")
    stat = KEEP_ALIVE;
  else
    stat = request_data.status;
  size_t zise = (*resp.begin()).size();
  return HeadersBuilder::build(R200, stat, content_type, zise,
                               serverConfig.host, serverConfig.port, "", resp);
}

} // namespace http