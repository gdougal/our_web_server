//
// Created by Lonmouth Mallador on 6/29/21.
//

#ifndef WEB_SERVER_RESPONSEUTILS_HPP
#define WEB_SERVER_RESPONSEUTILS_HPP

#include <string>
#include <filesystem>

using namespace std;

static const string PATH_TO_ROOT = "/Users/lmallado/Desktop/our_web_server";

class ResponseUtils {
public:
  static bool is_directory(const string &path);
};

#endif // WEB_SERVER_RESPONSEUTILS_HPP
