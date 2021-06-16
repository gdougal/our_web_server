//
// Created by Gilberto Dougal on 6/6/21.
//

#include "HTTP_handler.hpp"
#include "http_stuff.hpp"
#include "cstring"

namespace http {


	HTTP_handler::HTTP_handler() : position_(0) {};
	HTTP_handler::~HTTP_handler() {}

	pair_str	HTTP_handler::pair_maker(const std::string &fo_pars, const std::string &delim) {
		size_t end_first = fo_pars.find_first_of(delim, position_);
		size_t start_second = fo_pars.find_first_not_of(delim, end_first);
		size_t end_second;
		if (delim == http::delim_method) {
			end_second = fo_pars.find_first_of(delim, start_second);
		} else
			end_second = end_line(fo_pars, start_second);

		if (end_first == std::string::npos || start_second == std::string::npos ||
				end_second == std::string::npos) {
			position_ = std::string::npos;
			return pair_str();
		}
		std::string key(fo_pars.data() + position_, end_first - position_);

		for (int i = 0; i != key.size() ; ++i) {
			key[i] = std::toupper(key[i]);
		}

		std::string value(fo_pars.data() + start_second, end_second - start_second);
		pair_str insert_pair(key, value);
		position_ = next_line(fo_pars, end_second);
		return insert_pair;
	}
	size_t		HTTP_handler::next_line(const std::string &fo_pars, const size_t pos) const {
		return end_line(fo_pars, pos) + strlen(http::line_end);
	}
	size_t		HTTP_handler::end_line(const std::string &fo_pars, const size_t pos) const {
		return fo_pars.find_first_of(http::line_end, pos);
	}
	size_t		HTTP_handler::end_block(const std::string &fo_pars) const {
		return fo_pars.find(http::query_end, position_, strlen(http::query_end));
	}

	bool			HTTP_handler::query_parsing(const std::string &fo_pars) {
		position_ = 0;
		query_.clear();
		size_t first_block = end_block(fo_pars);
		methos_and_path_ = pair_maker(fo_pars, http::delim_method);
		while (position_ < first_block) {
			pair_str insert_pair(pair_maker(fo_pars, http::delim_base));
			if (!insert_pair.first.empty())
				query_.insert(insert_pair);
		}
		position_ = first_block;
		return is_recvest_rly_end(fo_pars);
	}

	bool			HTTP_handler::parse_body_length(const std::string& src) {
		body_.append(position_, end_block(src));
		if (body_.size() == body_length_)
			return true;
		return false;
	};
	bool			HTTP_handler::parse_body_chunked(const std::string& src) {
		return true;
	};

	bool HTTP_handler::is_recvest_rly_end(const std::string &fo_pars) {
		map_str::const_iterator ret(query_.end());

		for(int i = 0; ret == query_.end(); ++i) {
			if (!http::header::body_type[i])
				return false;
			ret = query_.find(http::header::body_type[i]);
		}

		if ( std::isdigit(ret->second.at(0) ) ) {
			body_length_ = std::stoi(ret->second);
			position_ = position_ + strlen(query_end);
			return parse_body_length(fo_pars);
		}
		else if ( ret->second == http::header::chunked ) {
			return parse_body_chunked(fo_pars);
		}
		return true;
	}

	bool		HTTP_handler::is_recvest_end(const std::string &fo_pars)	const {
		if (end_block(fo_pars) != std::string::npos)
			return true;
		return false;
	}
	const std::string HTTP_handler::create_response()									const {
		std::string response;
		http::methods.find(methos_and_path_.first)->second(response, query_, methos_and_path_);
		return (response);
	}

}