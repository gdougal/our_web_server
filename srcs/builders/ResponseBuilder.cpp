//
// Created by Lonmouth Mallador on 6/19/21.
//

#include "ResponseBuilder.hpp"

ResponseBuilder::ResponseBuilder(const server_config &serverConfig,
                                 const t_request_data &data)
    : serverConfig(serverConfig), request_data(data) {
  auto first = serverConfig.routes.begin();
  auto last = serverConfig.routes.end();
  while (first != last) {
    server_routes.push_back(getDirectoryList((*first)->location));
    first++;
  }
}

string ResponseBuilder::search_file(route *r) {
  string path_res;
  if (r == nullptr)
    return "";
  path_res = r->directory + r->location +
             request_data.path.second.substr(r->location.length(),
                                             request_data.path.second.length() -
                                                 r->location.length());
  if (ResponseUtils::is_directory(path_res))
    path_res += r->index_file;
  return path_res;
}

string ResponseBuilder::build_response(methods qurey_type) {
  route *r = get_route();
  string path_res = search_file(r);
  std::string body;

  if (!is_method_allowed(qurey_type, r))
    return ErrorBuilder::build(405, serverConfig);

  switch (qurey_type) {
  case methods::GET: {
    if (ResponseUtils::is_directory(path_res) && r->autoindex)
      body = AutoindexResonseBuilder().build(
          serverConfig, PATH_TO_ROOT + path_res, request_data.path.second);
    else {
      body = ResponseUtils::read_from_file(path_res);
      if (body.empty())
        return ErrorBuilder::build(404, serverConfig);
    }
    break;
  }
  case methods::HEAD: {

    break;
  }
  case methods::PUT: {

    break;
  }
  case methods::POST: {
//    if (!r->cgi_path.empty()) {
//     // run cgi post
//    } else {
//      // run post
//    }
    break;
  }
  case methods::DELETE: {
//    if (!r->cgi_path.empty()) {
//      // run cgi delete
//    } else {
//      // run delete
//    }
    break;
  }
  }

  return HeadersBuilder::build(200, connection(KEEP_ALIVE), content_type(HTML),
                               body.length()) +
         body;
}

string ResponseBuilder::build_headers() { return std::string(); }

route *ResponseBuilder::get_route() {
  list<string> request_directories = getDirectoryList(request_data.path.second);
  route *result = nullptr;

  auto first_server_routes = server_routes.begin();
  auto last_server_routes = server_routes.end();
  auto current_route = serverConfig.routes.begin();

  int max_match_words_count = 0;
  while (first_server_routes != last_server_routes) {
    auto f_word = first_server_routes->begin();
    auto l_word = first_server_routes->end();

    auto f_request_word = request_directories.begin();
    auto l_request_word = request_directories.end();

    int match_words = 0;
    while (f_word != l_word) {
      if (f_request_word == l_request_word) {
        match_words = 0;
        break;
      }
      if (*f_word == *f_request_word) {
        match_words++;
      } else {
        match_words = 0;
        break;
      }
      f_request_word++;
      f_word++;
    }
    if (match_words > max_match_words_count) {
      max_match_words_count = match_words;
      result = current_route->get();
    }
    current_route++;
    first_server_routes++;
  }

  return result;
}

list<string> ResponseBuilder::getDirectoryList(string src) {
  list<string> res;
  res.push_front("/");

  if (src == "/")
    return res;
  for (int first = 0, second = src.find('/', first + 1); first < second;
       first = second, second = src.find('/', second + 1)) {
    if (first < second)
      res.push_back(src.substr(first + 1, second - 1 - first));
  }
  return res;
}

bool ResponseBuilder::is_method_allowed(methods request_method, route *r) {
  auto first = r->methods_allowed.begin();
  auto last = r->methods_allowed.end();

  while (first != last) {
    if (*first == request_method)
      return true;
    first++;
  }
  return false;
}

ResponseBuilder::~ResponseBuilder() {}
