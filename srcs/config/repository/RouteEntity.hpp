//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_ROUTEENTITY_HPP
#define WEB_SERVER_ROUTEENTITY_HPP

#include "list"
#include <string>

enum methods { GET, POST, DELETE, HEAD, PUT };

struct route {
  std::string location;
  std::string directory;
  std::string index_file;
  std::string redirect_path;
  std::string save_path;
  size_t body_size;
  bool autoindex;
  std::list<methods> methods_allowed;

  route() {}

  route(const std::string &location, const std::string &directory,
        bool autoindex, const std::string &indexFile,
        const std::string &redirectPath,
        const std::list<methods> &methodsAllowed, const std::string &save_path,
        size_t body_size)
      : location(location), directory(directory),
        methods_allowed(methodsAllowed), autoindex(autoindex),
        index_file(indexFile), redirect_path(redirectPath),
        save_path(save_path), body_size(body_size) {}

  route(const route &route) {
    if (this != &route) {
      *this = route;
    }
  }
  route &operator=(const route &route) {
    this->location = route.location;
    this->directory = route.directory;
    this->index_file = route.index_file;
    this->redirect_path = route.redirect_path;
    this->autoindex = route.autoindex;
    this->save_path = route.save_path;
    this->body_size = route.body_size;
    this->methods_allowed = route.methods_allowed;
    return *this;
  }
  ~route() {}
};

#endif // WEB_SERVER_ROUTEENTITY_HPP
