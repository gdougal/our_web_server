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

  void Get::build_response(const server_config &serverConfig,
                           const t_request_data &request_data,
                           std::list<std::vector<uint8_t> > &resp) {
    std::string content_type = ".html";
    if (is_directory(request_data.path) &&
        request_data.request_route.autoindex) {
      AutoindexResonseBuilder().build(
              serverConfig, PATH_TO_ROOT + request_data.path, request_data.path,
              resp);
    } else {
      ResponseUtils::read_from_file(request_data.path, resp);
      content_type = ResponseUtils::get_content_type(request_data.path);
      if ( resp.empty() || (!resp.empty() &&  (*resp.begin()).empty() ) ) {
        ErrorBuilder::build(ER404, serverConfig, resp);
        return;
      }
    }
    size_t zise = (*resp.begin()).size();
    HeadersBuilder::build(R200, connection(KEEP_ALIVE), content_type,
                          zise, serverConfig.host,
                          serverConfig.port, resp);
  }

}