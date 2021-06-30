//
// Created by Gilberto Dougal on 6/14/21.
//

#ifndef WEB_SERVER_HTTP_STUFF_HPP
#define WEB_SERVER_HTTP_STUFF_HPP

#include "ResponseBuilder.hpp"
#include "RouteEntity.hpp"
#include "request_data.hpp"
#include <fstream>
#include <iostream>

namespace http {

typedef std::map<std::string, std::string> map_str;
typedef std::pair<std::string, std::string> pair_str;

namespace query_type {
static const char GET[] = "GET";
static const char POST[] = "POST";
static const char DELETE[] = "DELETE";
static const char HEAD[] = "HEAD";
} // namespace query_type

namespace header {
static const char cont_len[] = "CONTENT-LENGTH";
static const char encoding[] = "TRANSFER-ENCODING";
static const char chunked[] = "chunked";
} // namespace header

static const char query_end[] = "\r\n\r\n";
static const char line_end[] = "\r\n";
static const char delim_method[] = " ";
static const char delim_base[] = " :";
static const char request_init[] =
    "HTTP/1.1 200 OK\r\nVersion: HTTP/1.1\r\nConnection: "
    "keep-alive\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: ";
static const char bad_request[] =
    "HTTP/1.1 400 Bad Request\r\nConnection: "
    "close\r\n\r\n"; /* Server:
                        abracadabra\r\nContent-Type:
                        text/html\r\nContent-Length:
                        126\r\n */

static std::string query_get(const server_config &config,
                             const t_request_data &data) {
  std::list<route> routes;
  std::list<methods> allowed_methods;
  allowed_methods.push_back(methods(GET));
  allowed_methods.push_back(methods(HEAD));
  std::map<int, string> error_pages;
//  error_pages.insert(pair<int, string>(404, "/pages_root/error_pages/404_error"
//                                            ".html"));
  error_pages.insert(pair<int, string>(403, "/pages_root/error_pages/403_error"
                                            ".html"));
  routes.push_back(route("/pages/some/", "/data/www", false, "simple.html",
                         "/pages/lyubaya.html", "/pages/lyubaya.html",
                         allowed_methods));
  routes.push_back(route("/", "/pages_root", true, "", "/pages/lyubaya.html",
                         "/pages/lyubaya.html", allowed_methods));

  routes.push_back(route("/data/www/html/", "/pages_root", false,
                         "simple.html"
                         ".html",
                         "/pages/lyubaya.html", "/pages/lyubaya.html",
                         allowed_methods));

  server_config serverConfig("127.0.0.1", "8000", "lol", 21, error_pages,
                             routes);
  return ResponseBuilder(serverConfig, data).build_response(methods(GET));
};

static std::string query_post(const server_config &config,
                              const t_request_data &data) {
  return "Я не ебу, что делать";
};

static std::string query_delete(const server_config &config,
                                const t_request_data &data) {
  return "Я тоже не ебу, что делать";
};

static std::string query_head(const server_config &config,
                              const t_request_data &data) {
  return "Я тоже не ебу, что делать";
};

namespace {
typedef std::string(t_f)(const server_config &, const t_request_data &);
struct functor {
  t_f *function;
  std::string operator()(const server_config &serverConfig,
                         const t_request_data &data) const {
    return (*function)(serverConfig, data);
  };
  explicit functor(t_f *function) : function(function) {}
};

static std::map<std::string, functor> initialize() {
  std::map<std::string, functor> init_methods;
  init_methods.insert(
      std::pair<std::string, functor>(query_type::GET, functor(query_get)));
  init_methods.insert(
      std::pair<std::string, functor>(query_type::POST, functor(query_post)));
  init_methods.insert(std::pair<std::string, functor>(query_type::DELETE,
                                                      functor(query_delete)));
  init_methods.insert(
      std::pair<std::string, functor>(query_type::HEAD, functor(query_head)));
  return init_methods;
}
} // namespace

static const std::map<std::string, functor> methods(initialize());
} // namespace http

#endif // WEB_SERVER_HTTP_STUFF_HPP
