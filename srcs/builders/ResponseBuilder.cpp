//
// Created by Lonmouth Mallador on 6/19/21.
//

#include "ResponseBuilder.hpp"
#include <http_stuff.hpp>

ResponseBuilder::ResponseBuilder(const server_config &serverConfig,
                                 const map<string, string>& headers,
                                 const pair<string, string>& path)
    : serverConfig(serverConfig), headers(headers), path(path) {}

bool ResponseBuilder::search_file(methods qurey_type) {
  string search_path =
      path.second.substr(path.second.find('/'), path.second.rfind('/'));
  std::cout << "search path is : " + search_path << std::endl;
  get_route();
  return true;
}

string ResponseBuilder::build_response(methods qurey_type) {
  if (!search_file(qurey_type))
    return build_error(404);
  std::ifstream page("/home/local/REGION/as.doynikov/clion_pj/hm" + path.second);
  std::string body;
  std::string tmp;
  while (std::getline(page, tmp)) {
    body += tmp;
  };
  return http::request_init + std::to_string(body.length()) + http::query_end +
         body;
}

string ResponseBuilder::build_error(int error_code) { return std::string(); }

string ResponseBuilder::build_headers() { return std::string(); }

bool ResponseBuilder::get_route() {
  pair<int, route> max_equals(0, serverConfig.routes.front());
  list<route>::const_iterator first = serverConfig.routes.begin();
  list<route>::const_iterator last = serverConfig.routes.end();

  list<list<string>> res;
  while (first != last) {
    res.push_front(getDirectoryList(path.second));
    first++;
  }

  list<list<string>>::iterator f = res.begin();
  list<list<string>>::iterator l = res.end();

  int i = 0;
  while (f != l) {
    list<string>::iterator b = f->begin();
    list<string>::iterator e = f->end();
    std::cout << i << " route is" << endl;
    while (b != e) {
      std::cout << *b << endl;
      b++;
    }
    i++;
    f++;
  }

  return true;
}

list<string> ResponseBuilder::getDirectoryList(string src) {
  list<string> res;
  for (int first = 0, second = src.find('/', first + 1); first < second;
       first = second, second = src.find('/', second + 1)) {
    std::cout << " begin is " << first << " second is " << second
              << " result"
                 " is "
              << src.substr(first + 1, second - 1 - first) << endl;
    if (first < second)
      res.push_back(src.substr(first + 1, second - 1 - first));
  }
  return res;
}