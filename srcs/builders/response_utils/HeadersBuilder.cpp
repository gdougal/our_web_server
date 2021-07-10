//
// Created by Lonmouth Mallador on 6/28/21.
//

#include "HeadersBuilder.hpp"
#include <iostream>

namespace http {
  static const std::map<handl_ret_codes, std::string> response_code_description =
          {{R100,  "Continue"},
           {R200,  "OK"},
           {R201,  "Created"},
           {ER204, "No Content"},
           {ER400, "Bad Request"},
           {ER403, "Forbidden"},
           {ER404, "Not Found"},
           {ER405, "Method Not Allowed"},
           {ER413, "Payload Too Large"},
           {ER500, "Internal Server Error"}};

  void HeadersBuilder::build(handl_ret_codes response_code,
                             connection connectionType,
                             const std::string &contentType,
                             size_t contentLength,
                             const std::string &host,
                             const std::string &port,
                             std::list<std::vector<uint8_t>> &resp) {
    std::string header = "";
    header += PROTOCOL + std::to_string(response_code) + " " +
              response_code_description.find(response_code)->second +
              parse_utils::line_end;
    header += PROTOCOL_VERSION + parse_utils::line_end;
    header +=
            CONNECTION + get_connection_type(connectionType) +
            parse_utils::line_end;
    header += CONTENT_TYPE + contentType + parse_utils::line_end;
    header +=
            CONTENT_LENGHT + std::to_string(contentLength);// +
      //      parse_utils::line_end;
//    header += HOST + "http://" + host + ":" + port;

    header += parse_utils::query_end;

    resp.push_front(std::vector<uint8_t>(header.begin(), header.end()));
  }

  std::string HeadersBuilder::get_connection_type(connection conn) {
    std::string connection_str = "";
    switch (conn) {
      case connection::KEEP_ALIVE:
        connection_str = KEEP_ALIVE_STR;
        break;
      case connection::CLOSE:
        connection_str = CLOSE_STR;
        break;
    }
    return connection_str;
  }

}// namespace http