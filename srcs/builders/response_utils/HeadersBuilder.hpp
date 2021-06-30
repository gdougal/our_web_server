//
// Created by Lonmouth Mallador on 6/28/21.
//

#ifndef WEB_SERVER_HEADERSBUILDER_HPP
#define WEB_SERVER_HEADERSBUILDER_HPP

#include "ConfigRepository.hpp"
#include "ParseUtils.hpp"
#include <string>

using namespace std;

static const string PROTOCOL = "HTTP/1.1 ";
static const string PROTOCOL_VERSION = "Version: HTTP/1.1";
static const string CONNECTION = "Connection: ";
static const string CONTENT_TYPE = "Content-Type: ";
static const string CONTENT_LENGHT = "Content-Length: ";

static const string KEEP_ALIVE_STR = "keep-alive";
static const string CLOSE_STR = "close";

static const string HTML_STR = "text/html";
static const string CSS_STR = "text/css";
static const string JS_STR = "image/javascript";
static const string JPG_STR = "image/jpeg";
static const string PNG_STR = "image/png";
static const string BMP_STR = "image/bmp";
static const string UNDEFINED_STR = "UNDEFINED";

static const map<int, string> response_code_description = {
    {100, "Continue"},          {200, "OK"},
    {201, "Created"},           {204, "No Content"},
    {400, "Bad Request"},       {403, "Forbidden"},
    {404, "Not Found"},         {405, "Method Not Allowed"},
    {413, "Payload Too Large"}, {500, "Internal Server Error"}};

class HeadersBuilder {
private:
  static string get_connection_type(connection conn);
  static string get_content_type(content_type type);

public:
  static string build(int response_code, connection connectionType,
                      content_type contentType, int contentLength);
};

#endif // WEB_SERVER_HEADERSBUILDER_HPP
