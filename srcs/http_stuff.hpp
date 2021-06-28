//
// Created by Gilberto Dougal on 6/14/21.
//

#ifndef WEB_SERVER_HTTP_STUFF_HPP
#define WEB_SERVER_HTTP_STUFF_HPP

#include "ResponseBuilder.hpp"
#include "RouteEntity.hpp"
#include <fstream>
#include <iostream>
#include <map>

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

static void query_get(std::string &response, const map_str &header,
                      const pair_str &path) {
  std::list<route> routes;
  std::list<methods> allowed_methods;
  allowed_methods.push_back(methods(GET));
  allowed_methods.push_back(methods(HEAD));
  std::list<pair<int, string>> error_pages;
  error_pages.push_back(pair<int, string>(404, "/pages/error_pages.html"));
  routes.push_back(route("/pages/some/", "/data/www", false, "simple.html",
                         "/pages/lyubaya.html", "/pages/lyubaya.html",
                         allowed_methods));
  routes.push_back(route("/", "/pages_root", false, "simple.html",
                         "/pages/lyubaya.html", "/pages/lyubaya.html",
                         allowed_methods));

  routes.push_back(route("/data/www/html/", "/pages_root", false, "simple.html"
                                                    ".html",
                         "/pages/lyubaya.html", "/pages/lyubaya.html",
                         allowed_methods));

  server_config serverConfig("127.0.0.1", "8000", "lol", 21, error_pages,
                             routes);
  response =
      ResponseBuilder(serverConfig, header, path).build_response(methods(GET));
};

static void query_post(std::string &response, const map_str &header,
                       const pair_str &path) {
  response = "Я не ебу, что делать";
  std::cout << response << std::endl;
};

static void query_delete(std::string &response, const map_str &header,
                         const pair_str &path) {
  response = "Я тоже не ебу, что делать";
  std::cout << response << std::endl;
};

static void query_head(std::string &response, const map_str &header,
                       const pair_str &path) {
  response = "Я тоже не ебу, что делать";
  std::cout << response << std::endl;
};

namespace {
typedef void(t_f)(std::string &, const map_str &, const pair_str &);
struct functor {
  t_f *function;
  void operator()(std::string &response, const map_str &header,
                  const pair_str &path) const {
    (*function)(response, header, path);
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
