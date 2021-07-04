//
// Created by Lonmouth Mallador on 6/28/21.
//

#include "HeadersBuilder.hpp"

static const std::map<content_type, std::string> content_type_map = {
				{HTML, "text/html"},						{JS, "image/javascript"},
				{CSS, "text/css"},							{JPEG, "image/jpeg"},
				{UNDEFINED, "UNDEFINED"},			{PNG, "image/png"},
				{BMP, "image/bmp"}																						};

static const std::map<handl_ret_codes, std::string> response_code_description = {
				{R100, "Continue"},          {R200, "OK"},
				{R201, "Created"},           {ER204, "No Content"},
				{ER400, "Bad Request"},       {ER403, "Forbidden"},
				{ER404, "Not Found"},         {ER405, "Method Not Allowed"},
				{ER413, "Payload Too Large"}, {ER500, "Internal Server Error"} };

std::string HeadersBuilder::build(handl_ret_codes response_code, connection connectionType,
                             content_type contentType, int contentLength) {
	std::string header = "";
  header += PROTOCOL + std::to_string(response_code) + " " +
            response_code_description.find(response_code)->second +
            parse_utils::line_end;
  header += PROTOCOL_VERSION + parse_utils::line_end;
  header += CONNECTION + get_connection_type(connectionType) +
            parse_utils::line_end;
  header += CONTENT_TYPE + get_content_type(contentType) +
            parse_utils::line_end;
  header += CONTENT_LENGHT + std::to_string(contentLength) + parse_utils::query_end;
  header += parse_utils::query_end;
  return header;
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

std::string HeadersBuilder::get_content_type(content_type type) {
	std::string content_type = "";
  auto elem = content_type_map.find(type);
  if (elem != content_type_map.end())
  	content_type + elem->second;
  return content_type;
}
