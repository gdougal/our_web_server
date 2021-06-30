//
// Created by Gilberto Dougal on 6/6/21.
//

#include "Handler.hpp"
#include "cstring"
#include "ParseUtils.hpp"
#include "ResponseBuilder.hpp"
#include "manual_types.h"

namespace http {

Handler::Handler() : position_(0), body_parse(nullptr), body_length_(0){};
Handler::~Handler() {}

pair_str Handler::pair_maker(const std::string &fo_pars,
                             const std::string &delim) {
  size_t end_first = fo_pars.find_first_of(delim, position_);
  size_t start_second = fo_pars.find_first_not_of(delim, end_first);
  size_t end_second;
  if (delim == parse_utils::delim_method) {
    end_second = fo_pars.find_first_of(delim, start_second);
  } else
    end_second = end_line(fo_pars, start_second);

  if (end_first == std::string::npos || start_second == std::string::npos ||
      end_second == std::string::npos) {
    position_ = std::string::npos;
    return pair_str();
  }
  std::string key(fo_pars.data() + position_, end_first - position_);

  for (int i = 0; i != key.size(); ++i) {
    key[i] = std::toupper(key[i]);
  }

  std::string value(fo_pars.data() + start_second, end_second - start_second);
  pair_str insert_pair(key, value);
  position_ = next_line(fo_pars, end_second);
  return insert_pair;
}

void Handler::header_part(const std::string &fo_pars) {
  size_t first_block = end_block(fo_pars);
  methos_and_path_ = pair_maker(fo_pars, parse_utils::delim_method);
  while (position_ < first_block) {
    pair_str insert_pair(pair_maker(fo_pars, parse_utils::delim_base));
    if (!insert_pair.first.empty())
      header_.insert(insert_pair);
  }
  position_ = first_block + strlen(parse_utils::query_end);
}

size_t Handler::next_line(const std::string &fo_pars, const size_t pos) const {
  return end_line(fo_pars, pos) + strlen(parse_utils::line_end);
}

size_t Handler::end_line(const std::string &fo_pars, const size_t pos) const {
  return fo_pars.find_first_of(parse_utils::line_end, pos);
}

size_t Handler::end_block(const std::string &fo_pars) const {
  return fo_pars.find(parse_utils::query_end, position_,
                      strlen(parse_utils::query_end));
}

bool Handler::query_parsing(const std::string &fo_pars) {
  if (body_parse)
    return body_parse(*this, fo_pars);
  header_part(fo_pars);
  return is_recvest_rly_end(fo_pars);
}

bool Handler::is_recvest_rly_end(const std::string &fo_pars) {
  map_str::const_iterator find;
  if ((find = header_.find(parse_utils::encoding)) != header_.end()) {
    if (find->second == parse_utils::chunked) {
      body_parse = parse_body_chunked;
    }
  } else if ((find = header_.find(parse_utils::cont_len)) != header_.end()) {
    body_length_ = std::stoi(find->second);
    body_parse = parse_body_length;
  }
  if (body_parse != nullptr) {
    return (*body_parse)(*this, fo_pars);
  }
  return true;
}

bool Handler::parse_body_length(Handler &obj, const std::string &src) {
  if (src.size() - obj.position_ != obj.body_length_)
    return false;
  obj.body_.append(src.substr(obj.position_, obj.body_length_));
  std::cout << obj.body_ << std::endl;
  if (obj.body_.size() == obj.body_length_)
    return true;
  return false;
};

bool Handler::parse_body_chunked(Handler &obj, const std::string &src) {
  if (src.substr(src.size() - strlen(parse_utils::query_end)) !=
      parse_utils::query_end)
    return false;
  size_t tmp = obj.end_line(src, obj.position_);
  std::string number(src.substr(obj.position_, tmp - obj.position_));
  obj.body_length_ = std::stoi(number, nullptr, 16);
  if (obj.body_length_ == 0)
    return true;
  obj.position_ = obj.next_line(src, obj.position_);
  obj.body_.append(src.substr(obj.position_, obj.body_length_));
  obj.position_ = obj.next_line(src, obj.position_);
  return parse_body_chunked(obj, src);
};

bool Handler::is_recvest_end(const std::string &fo_pars) const {
  if (end_block(fo_pars) != std::string::npos || body_parse)
    return true;
  return false;
}

const std::string Handler::create_response(const server_config &config) {
  ResponseBuilder builder(config, t_request_data{header_, methos_and_path_, body_});
  std::string response(builder.build_response(parse_utils::get_enum_methods(methos_and_path_.first)));
  after_all();
  return (response);
}

void Handler::after_all() {
  position_ = 0;
  header_.clear();
  body_.clear();
  body_parse = nullptr;
  body_length_ = 0;
}
} // namespace http