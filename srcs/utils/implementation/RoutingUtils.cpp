//
// Created by Gilberto Dougal on 7/3/21.
//
#include "RoutingUtils.hpp"
#include "ParseUtils.hpp"
#include "ConfigRepository.hpp"
#include "CommonUtils.hpp"


namespace routing_utils {

	Optional_simple<route> get_route(const std::string &url, const server_config &serverConfig) {
		std::list<std::string> request_directories = parse_utils::getDirectoryList(url);
		Optional_simple<route> result;

		auto first_server_routes = serverConfig.routes.begin();
		auto last_server_routes = serverConfig.routes.end();

		int max_match_words_count = 0;
		while (first_server_routes != last_server_routes) {
			auto f_word = first_server_routes->get()->directory_word_list.begin();
			auto l_word = first_server_routes->get()->directory_word_list.end();

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
//                std::find

		return result;
	}

}
