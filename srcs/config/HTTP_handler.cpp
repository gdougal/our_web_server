//
// Created by Gilberto Dougal on 6/6/21.
//

#include "HTTP_handler.hpp"

HTTP_handler::HTTP_handler() : position_(0) {};
HTTP_handler::~HTTP_handler()	{}

pair_str	HTTP_handler::pair_maker(const std::string& fo_pars, const std::string& delim) {
		size_t end_first = fo_pars.find_first_of(delim, position_);
		size_t start_second = fo_pars.find_first_not_of(delim, end_first);
		size_t end_second;
		if (delim == http::delim_method) {
			end_second = fo_pars.find_first_of(delim, start_second);
		}
		else
			end_second = end_line(fo_pars, start_second);

		if (end_first == std::string::npos || start_second == std::string::npos || end_second == std::string::npos) {
			position_ = std::string::npos;
			return pair_str();
		}
		std::string key(fo_pars.data() + position_, end_first - position_);
		std::string value(fo_pars.data() + start_second, end_second - start_second);
		pair_str insert_pair(key, value);
		position_ = next_line(fo_pars, end_second);
		return insert_pair;
}

void		HTTP_handler::get_string_map(const std::string& fo_pars) {
		pair_str insert_pair(pair_maker(fo_pars, http::delim_base));
		if (!insert_pair.first.empty())
			query_.insert(insert_pair);
}

size_t	HTTP_handler::next_line(const std::string& fo_pars, const size_t pos)	const { return end_line(fo_pars, pos) + strlen(http::line_end); }
size_t	HTTP_handler::end_line(const std::string& fo_pars, const size_t pos)	const { return fo_pars.find_first_of(http::line_end, pos); }
size_t	HTTP_handler::end_block(const std::string& fo_pars)										const { return fo_pars.find(http::query_end, position_, strlen(http::query_end)); }

void HTTP_handler::header_parse(const std::string& fo_pars, size_t end_block) {
	while (position_ != std::string::npos && position_ < end_block) {
		get_string_map(fo_pars);
	}
}

void HTTP_handler::query_parsing(const std::string& fo_pars) {
	position_ = 0;
	query_.clear();
	size_t first_block = end_block(fo_pars);
	methos_and_path_ = pair_maker(fo_pars, http::delim_method);
	header_parse(fo_pars, first_block);
//	if (methos_and_path_.first == "GET") {
//
//	}
//	else
//		int a = 0;
	/*Not get*/
}

bool HTTP_handler::is_recvest_end(const std::string& fo_pars) const {
	if (end_block(fo_pars) != std::string::npos)
		return true;
	return false;
}

const std::string HTTP_handler::create_response() const {
	if (methos_and_path_.second.empty())
		return http::bad_request;
	std::ifstream	page("/Users/gdougal/Desktop/our_web_server/pages" + methos_and_path_.second);
	std::string		body;
	std::string		tmp;
	while (std::getline(page, tmp)) { body += tmp; };

	return ( http::request_init
					+ std::to_string(body.length())
					+ http::query_end
					+ body);
}

