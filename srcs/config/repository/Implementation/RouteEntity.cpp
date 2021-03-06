//
// Created by Gilberto Dougal on 7/3/21.
//
#include "RouteEntity.hpp"
#include "ParseUtils.hpp"

namespace http {

  route::route(const ConfigParser::Section &ref, int idx)
          : location(ref.getStrValue("route", idx)),
            directory(ref.getStrValue("directory", idx)),
            index_file(ref.getStrValue("index_file", idx)),
            redirect_path(ref.getStrValue("redirection", idx)),
            save_path(ref.getStrValue("save_path", idx)),
            body_size(std::stoi(ref.getStrValue("limit_body_size", idx, "-1"))),
            autoindex(false) {
    if (ref.getStrValue("autoindex", idx) == "on")
      autoindex = true;
    std::string meth(ref.getStrValue("methods_allowed", idx));
    for (size_t pos = 0, end;; pos = meth.find(';', pos + 1) + 1) {
      end = meth.find(';', pos);
      if (end == std::string::npos)
        end = meth.size();
      auto part = meth.substr(pos, end);
      for (int idx_ = 0; static_cast<methods>(idx_) != methods::LAST_METH; ++idx_) {
        if (enum_str[idx_] == part) {
          methods_allowed.push_back(static_cast<methods>(idx_));
          break;
        }
      }
      if (end == meth.size())
        break;
    }
    directory_word_list = (parse_utils::getDirectoryList(location));
  }

  route &route::operator=(const route &route) {
    this->location = route.location;
    this->directory = route.directory;
    this->index_file = route.index_file;
    this->redirect_path = route.redirect_path;
    this->save_path = route.save_path;
    this->body_size = route.body_size;
    this->autoindex = route.autoindex;
    this->methods_allowed = route.methods_allowed;
    return *this;
  };

  route::route(const route &route) {
    if (&route != this)
      *this = route;
  }

}