//
// Created by Lonmouth Mallador on 6/29/21.
//

#include "ResponseUtils.hpp"
#include <sys/stat.h>

bool ResponseUtils::is_directory(const string &path) {
  struct stat s;
  string str = PATH_TO_ROOT + path.c_str();
  if (stat(str.c_str(), &s) == 0)
    if (s.st_mode & S_IFDIR) {
      return true;
    }
  return false;
}