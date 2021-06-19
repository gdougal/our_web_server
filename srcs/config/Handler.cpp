//
// Created by Gilberto Dougal on 6/6/21.
//

#include "Handler.hpp"
#include "http_stuff.hpp"
#include "cstring"

namespace http {


	Handler::Handler() : position_(0), body_parse(nullptr), body_length_(0), MAX_LENGTH_(0) {};
	Handler::~Handler() {}

	//HEADER PARSING
	pair_str	Handler::pair_maker(const std::string &fo_pars, const std::string &delim) {
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
	void			Handler::header_part(const std::string &fo_pars) {
		size_t first_block = end_block(fo_pars);
		methos_and_path_ = pair_maker(fo_pars, http::delim_method);
		while (position_ < first_block) {
			pair_str insert_pair(pair_maker(fo_pars, http::delim_base));
			if (!insert_pair.first.empty())
				query_.insert(insert_pair);
		}
		position_ = first_block + strlen(http::query_end);
	}
	size_t		Handler::next_line(const std::string &fo_pars, const size_t pos) const {
		return end_line(fo_pars, pos) + strlen(http::line_end);
	}
	size_t		Handler::end_line(const std::string &fo_pars, const size_t pos) const {
		return fo_pars.find_first_of(http::line_end, pos);
	}
	size_t		Handler::end_block(const std::string &fo_pars) const {
		return fo_pars.find( http::query_end, position_, strlen(http::query_end) );
	}
	bool			Handler::query_parsing(const std::string &fo_pars) {
		if (body_parse)
			return body_parse(*this, fo_pars);
		header_part(fo_pars);
		return is_recvest_rly_end(fo_pars);
	}

	bool			Handler::is_recvest_rly_end(const std::string &fo_pars) {
		map_str::const_iterator find;
		if (( find = query_.find(header::encoding) ) != query_.end()) {
			if (find->second == header::chunked) {
				body_parse = parse_body_chunked;
			}
		}
		else if ((find = query_.find(header::cont_len) ) != query_.end()) {
			body_length_ = std::stoi(find->second);
			body_parse = parse_body_length;
		}
		if (body_parse != nullptr) {
			return (*body_parse)(*this, fo_pars);
		}
		return true;
	}

	bool			Handler::parse_body_length(Handler& obj, const std::string& src) {
		obj.body_.append(src.substr(obj.position_));
		if (obj.body_.size() == obj.body_length_)
			return true;
		return false;
	};

	bool			Handler::parse_body_chunked(Handler& obj, const std::string& src) {
		if (src.substr(src.size() - strlen(http::query_end)) != http::query_end)
			return false;
	size_t tmp = obj.end_line(src, obj.position_);
	if (tmp == std::string::npos)
		return false;
	std::string number(src.substr(obj.position_, tmp - obj.position_));
	obj.body_length_ = std::stoi(number,
													nullptr,
												16);
		if (obj.body_length_ == 0)
			return true;
		obj.position_ = obj.next_line(src, obj.position_);
		obj.body_.append(src.substr(obj.position_, obj.body_length_));
		obj.position_ = obj.next_line(src, obj.position_);
		return parse_body_chunked(obj, src);
	};
	
	bool			Handler::append_query(const std::string& src) {
			return (*body_parse)(*this, src);
		}

	bool		Handler::is_recvest_end(const std::string &fo_pars)	const {
		if (end_block(fo_pars) != std::string::npos)
			return true;
		return false;
	}
	const		std::string Handler::create_response() {
		std::string response;
		http::methods.find(methos_and_path_.first)->second(response, query_, methos_and_path_);
		after_all();
		return (response);
	}

	void Handler::after_all() {
		position_ = 0;
		query_.clear();
		body_.clear();
		body_parse = nullptr;
		body_length_ = 0;
		MAX_LENGTH_ = 0;
	}

}