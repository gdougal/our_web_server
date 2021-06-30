//
// Created by Lonmouth Mallador on 6/30/21.
//

#ifndef WEB_SERVER_PARSEUTILS_HPP
#define WEB_SERVER_PARSEUTILS_HPP

namespace parse_utils {

static const char query_end[] = "\r\n\r\n";
static const char line_end[] = "\r\n";
static const char delim_method[] = " ";
static const char delim_base[] = " :";

static const char GET[] = "GET";
static const char POST[] = "POST";
static const char DELETE[] = "DELETE";
static const char HEAD[] = "HEAD";
static const char PUT[] = "PUT";
static const char cont_len[] = "CONTENT-LENGTH";
static const char encoding[] = "TRANSFER-ENCODING";
static const char chunked[] = "chunked";

static methods get_enum_methods(const std::string &method_str) {
  if (method_str == GET)
    return methods::GET;
  if (method_str == PUT)
    return methods::PUT;
  if (method_str == POST)
    return methods::POST;
  if (method_str == HEAD)
    return methods::HEAD;
  //  if (method_str == DELETE)
  return methods::DELETE;
}

} // namespace parse_utils

#endif // WEB_SERVER_PARSEUTILS_HPP
