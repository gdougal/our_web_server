//
// Created by Lonmouth Mallador on 6/29/21.
//

#include "ResponseUtils.hpp"
#include "CommonUtils.hpp"
#include "map"
#include <fstream>
#include "unistd.h"
#include "vector"

namespace ResponseUtils {

static const std::map<std::string, std::string> class_of_content = {
    {"html", "text/html"},  {"js", "text/javascript"}, {"css", "text/css"},
    {"jpeg", "image/jpeg"}, {"jpg", "image/jpg"},      {"png", "image/png"},
    {"bmp", "image/bmp"}};

void read_from_file(const std::string &path_res, std::list<std::vector<uint8_t> >& body) {
  std::ifstream page(path_res, std::ios::binary);
  page.seekg(0, page.end);
  ssize_t length = page.tellg();
  page.seekg(0, page.beg);
  if (length > 0) {
    std::vector<uint8_t> body_tmp;
    body_tmp.resize(length);
    page.read((char *)(body_tmp.data()), length);
    body.emplace_back(body_tmp);
    page.close();
  }
  else
    page.close();
}

std::string get_content_type(const std::string &filename) {
  size_t  pos = filename.find_last_of('.');
  if (pos == std::string::npos)
    return "text/plain";
  std::string fo_find(filename.substr(pos + 1));
  std::map<std::string, std::string>::const_iterator type =
      class_of_content.find(fo_find);
  if (type == class_of_content.end())
    return "text/plain";
  return type->second;
}

} // namespace ResponseUtils