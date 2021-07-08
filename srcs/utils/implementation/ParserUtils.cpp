//
// Created by Gilberto Dougal on 7/3/21.
//
#include "ParseUtils.hpp"

namespace http {

  namespace parse_utils {

    methods get_enum_methods(const std::string &method_str) {
      if (method_str == GET)
        return methods::GET;
      if (method_str == PUT)
        return methods::PUT;
      if (method_str == POST)
        return methods::POST;
      if (method_str == HEAD)
        return methods::HEAD;
      //  if (method_str == DELETE)
      return methods::DELETE;
    }

    std::list<std::string> getDirectoryList(const std::string &src) {
      std::list<std::string> res;
      res.push_front("/");
      if (src == "/") {
        return res;
      }
      for (int first = 0, second = src.find('/', first + 1); first < second;
           first = second, second = src.find('/', second + 1)) {
        if (first < second)
          res.push_back(src.substr(first + 1, second - 1 - first));
      }
      return res;
    }

  } // namespace parse_utils

} // namespace http