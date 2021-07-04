//
// Created by Lonmouth Mallador on 6/28/21.
//

#ifndef WEB_SERVER_HEADERSBUILDER_HPP
#define WEB_SERVER_HEADERSBUILDER_HPP

#include "ConfigRepository.hpp"
#include "ParseUtils.hpp"
#include <string>


static const std::string PROTOCOL = "HTTP/1.1 ";
static const std::string PROTOCOL_VERSION = "VERSION: HTTP/1.1";
static const std::string CONNECTION = "CONNECTION: ";
static const std::string CONTENT_TYPE = "CONTENT-TYPE: ";
static const std::string CONTENT_LENGHT = "CONTENT-LENGTH: ";

static const std::string KEEP_ALIVE_STR = "keep-alive";
static const std::string CLOSE_STR = "close";


//static const std::map<content_type, std::string> content_type_map = {
//				{HTML, "text/html"},						{JS, "image/javascript"},
//				{CSS, "text/css"},							{JPEG, "image/jpeg"},
//				{UNDEFINED, "UNDEFINED"},			{PNG, "image/png"},
//				{BMP, "image/bmp"}																						};
//
//static const std::map<handl_ret_codes, std::string> response_code_description = {
//    {R100, "Continue"},          {R200, "OK"},
//    {R201, "Created"},           {ER204, "No Content"},
//    {ER400, "Bad Request"},       {ER403, "Forbidden"},
//    {ER404, "Not Found"},         {ER405, "Method Not Allowed"},
//    {ER413, "Payload Too Large"}, {ER500, "Internal Server Error"} };

class HeadersBuilder {
private:
  static std::string get_connection_type(connection conn);
  static std::string get_content_type(content_type type);

public:
  static std::string build(handl_ret_codes response_code, connection connectionType,
                      content_type contentType, int contentLength);
};

#endif // WEB_SERVER_HEADERSBUILDER_HPP
