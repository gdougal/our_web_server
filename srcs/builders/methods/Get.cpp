//
// Created by Lonmouth Mallador on 7/4/21.
//

#include "Get.hpp"
#include "ParseUtils.hpp"
#include "CommonUtils.hpp"
#include "AutoindexResonseBuilder.hpp"
#include "ResponseUtils.hpp"
#include "ErrorBuilder.hpp"
#include "HeadersBuilder.hpp"
#include "iostream"

namespace http {

  connection Get::build_response(const server_config &serverConfig,
                           const t_request_data &request_data,
                           std::list<std::vector<uint8_t> > &resp) {
    std::string content_type = ".html";
    if (is_directory(serverConfig.path_to_root + request_data.path) &&
        request_data.request_route.autoindex) {
      AutoindexResonseBuilder().build(
              serverConfig, serverConfig.path_to_root + request_data.path, request_data.path,
              resp);
    } else {
      ResponseUtils::read_from_file(serverConfig.path_to_root + request_data.path, resp);
      content_type = ResponseUtils::get_content_type(request_data.path);
      if ( resp.empty() || (!resp.empty() &&  (*resp.begin()).empty() ) ) {
        return ErrorBuilder::build(ER404, serverConfig, resp);
      }
    }
    size_t zise = (*resp.begin()).size();
    return HeadersBuilder::build(R200, connection(KEEP_ALIVE), content_type,
                          zise, serverConfig.host,
                          serverConfig.port, "", resp);
  }

}