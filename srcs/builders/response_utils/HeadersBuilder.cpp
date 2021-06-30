//
// Created by Lonmouth Mallador on 6/28/21.
//

#include "HeadersBuilder.hpp"

string HeadersBuilder::build(int response_code, connection connectionType,
                             content_type contentType, int contentLength) {
  string header = "";
  header += PROTOCOL + to_string(response_code) + " " +
            response_code_description.find(response_code)->second +
            parse_utils::line_end;
  header += PROTOCOL_VERSION + parse_utils::line_end;
  header += CONNECTION + get_connection_type(connectionType) +
            parse_utils::line_end;
  header += CONTENT_TYPE + get_content_type(contentType) +
            parse_utils::line_end;
  header += CONTENT_LENGHT + to_string(contentLength) + parse_utils::query_end;
  header += parse_utils::query_end;
  return header;
}

string HeadersBuilder::get_connection_type(connection conn) {
  string connection_str = "";
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

string HeadersBuilder::get_content_type(content_type type) {
  string content_type = "";
  switch (type) {
  case content_type::HTML:
    content_type += HTML_STR;
    break;
  case content_type::CSS:
    content_type += CSS_STR;
    break;
  case content_type::JS:
    content_type += JS_STR;
    break;
  case content_type::JPEG:
    content_type += JPG_STR;
    break;
  case content_type::PNG:
    content_type += PNG_STR;
    break;
  case content_type::BMP:
    content_type += BMP_STR;
    break;
  case content_type::UNDEFINED:
    content_type += UNDEFINED_STR;
    break;
  }
  return content_type;
}
