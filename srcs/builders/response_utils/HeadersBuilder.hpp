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
static const std::string HOST = "Host: ";
static const std::string CONTENT_TYPE = "CONTENT-TYPE: ";
static const std::string CONTENT_LENGHT = "Content-Length: ";

static const std::string KEEP_ALIVE_STR = "keep-alive";
static const std::string CLOSE_STR = "close";


class HeadersBuilder {
private:
  static std::string get_connection_type(connection conn);

public:
  static void build(handl_ret_codes response_code, connection connectionType,
                      const std::string& contentType, size_t contentLength, const
                    std::string &host,
                    std::list<std::vector<uint8_t> >& );
};

#endif // WEB_SERVER_HEADERSBUILDER_HPP
