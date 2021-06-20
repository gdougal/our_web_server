//
// Created by Lonmouth Mallador on 6/19/21.
//

#ifndef WEB_SERVER_ROUTEENTITY_HPP
#define WEB_SERVER_ROUTEENTITY_HPP

#include <string>
enum methods { GET, POST, DELETE, HEAD };

using namespace std;


struct route {
  string directory;
  bool autoindex;
  string index_file;
  string redirect_path;
  string cgi_path;
  methods *methods_allowed;

  route(const string &directory, methods *methodsAllowed, bool autoindex,
        const string &indexFile, const string &redirectPath,
        const string &cgiPath)
      : directory(directory), methods_allowed(methodsAllowed),
        autoindex(autoindex), index_file(indexFile),
        redirect_path(redirectPath), cgi_path(cgiPath) {}
};

#endif // WEB_SERVER_ROUTEENTITY_HPP
