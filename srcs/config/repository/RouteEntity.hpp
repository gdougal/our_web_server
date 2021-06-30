//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_ROUTEENTITY_HPP
#define WEB_SERVER_ROUTEENTITY_HPP

#include "list"
#include <string>

enum methods { GET, POST, DELETE, HEAD, PUT};

using namespace std;

struct route {
  string location;
  string directory;
  bool autoindex;
  string index_file;
  string redirect_path;
  string cgi_path;
  std::list<methods> methods_allowed;

  route(const string &location, const string &directory,
        bool autoindex, const string &indexFile, const string &redirectPath,
        const string &cgiPath, std::list<methods> methodsAllowed)
      : location(location), directory(directory), methods_allowed(methodsAllowed),
        autoindex(autoindex), index_file(indexFile),
        redirect_path(redirectPath), cgi_path(cgiPath) {}
};

#endif // WEB_SERVER_ROUTEENTITY_HPP
