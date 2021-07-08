//
// Created by Gilberto Dougal on 7/3/21.
//
#include "RoutingUtils.hpp"
#include "CommonUtils.hpp"
#include "ConfigRepository.hpp"
#include "ParseUtils.hpp"
#include <iostream>
#include "optional.hpp"

namespace http {

  namespace routing_utils {

    ft::optional<route> get_route(std::string &url,
                                  const server_config &serverConfig) {
      ft::optional<route> result;
      std::string tmp_path;

      auto first_server_routes = serverConfig.routes.begin();
      auto last_server_routes = serverConfig.routes.end();

      int max_match_words_count = 0;
      while (first_server_routes != last_server_routes) {
        auto f_word = first_server_routes->get()->directory_word_list.begin();
        auto l_word = first_server_routes->get()->directory_word_list.end();
        tmp_path = first_server_routes->get()->directory + url;

        if (tmp_path.c_str()[tmp_path.size() - 1] != '/' &&
            is_directory(tmp_path) == IS_DIRECTORY)
          tmp_path = url + "/";
        else
          tmp_path = url;

        std::list<std::string> request_directories =
                parse_utils::getDirectoryList(tmp_path);
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
          result.set_value(*(first_server_routes->get()));
        }
        first_server_routes++;
      }
      //  { 2 } - serverConfig.routes
      //  { 2,3,4,5 } - request_directories
      //  for (auto& elem: request_directories) {
      //   auto iter =  std::find(serverConfig.routes.begin(), serverConfig.routes
      //                                                           .end(), elem);
      //   if ( iter != serverConfig.routes.end() ) {
      //     ++match_words;
      //   }
      //   if (serverConfig.routes.size() != match_words)
      //     idi nahui;
      //  }
      return result;
    }

  } // namespace routing_utils

} // namespace http