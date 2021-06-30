//
// Created by Lonmouth Mallador on 6/28/21.
//

#ifndef WEB_SERVER_HEADERSBUILDER_HPP
#define WEB_SERVER_HEADERSBUILDER_HPP

#include <string>
#include "ConfigRepository.hpp"

using namespace std;

static const string PROTOCOL = "HTTP/1.1 ";
static const string PROTOCOL_VERSION = "Version: HTTP/1.1";
static const string CONNECTION = "Connection: ";
static const string CONTENT_TYPE = "Content-Type: ";
static const string CONTENT_LENGHT = "Content-Length: ";

class HeadersBuilder {
public:
  static string build(int response_code, string response_description,
                      connection connectionType, content_type contentType,
                      int contentLength);
};

#endif // WEB_SERVER_HEADERSBUILDER_HPP
