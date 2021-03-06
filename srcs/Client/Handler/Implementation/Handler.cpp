//
// Created by Gilberto Dougal on 6/6/21.
//

#include "Handler.hpp"
#include "CommonUtils.hpp"
#include "ParseUtils.hpp"
#include "ResponseBuilder.hpp"
#include "RoutingUtils.hpp"
#include "optional.hpp"
#include "request_data.hpp"
#include "i_wanna_range_based_for.hpp"

namespace http {

Handler::Handler(const server_config &cfg)
    : position_(0), body_length_(0), max_body_(-1), config(cfg),
      body_parse(nullptr){};

Handler::~Handler() {}

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
  for (size_t i = 0; i != key.size(); ++i) {
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

std::string Handler::search_file() const {
  std::string path_res = cur_route_.directory + cur_route_.location;
  if (methos_and_path_.second.length() > cur_route_.location.length())
    path_res += methos_and_path_.second.substr(
        cur_route_.location.length(),
        methos_and_path_.second.length() - cur_route_.location.length());
  if (is_directory(config.path_to_root + path_res) == IS_DIRECTORY) {
    if (path_res.c_str()[path_res.size() - 1] == '/')
      path_res =
          path_res.substr(0, path_res.size() - 1) + cur_route_.index_file;
    else
      path_res = path_res + cur_route_.index_file;
  }
  return path_res;
}

handl_ret_codes Handler::file_checker(const std::string& target_path) const {
  req_file_status status = is_directory(config.path_to_root + target_path);
  if (status == IS_DIRECTORY)
    return ER403;
  else if (status == NOT_FOUND &&
           (header_.find(parse_utils::POST) == header_.end() ||
            header_.find(parse_utils::PUT) == header_.end())) {
    return ER404;
  }
  return CONTINUE;
}

handl_ret_codes Handler::route_searcher() {
  ft::optional<route> opt_route =
      routing_utils::get_route(methos_and_path_.second, config);
  if (!opt_route.is_val()) {
    return file_checker(methos_and_path_.second);
  }
  cur_route_ = opt_route.get();
  max_body_ = cur_route_.body_size;
  if (!opt_route.get().redirect_path.empty())
    return CONTINUE;
  size_t pos;
  if ((pos = methos_and_path_.second.find('?')) != std::string::npos) {
    query_string_ = methos_and_path_.second.substr(pos + 1);
    methos_and_path_.second.resize(pos);
  }
  if (!find_some(cur_route_.methods_allowed,
                 parse_utils::get_enum_methods(methos_and_path_.first)))
    return ER405;

  std::string target_path = search_file();
  handl_ret_codes cur_status = file_checker(target_path);

  if (cur_status == ER404 &&
      file_checker(methos_and_path_.second) != CONTINUE &&
      methos_and_path_.first != "PUT" && methos_and_path_.first != "POST")
    return (req_status_ = cur_status);
  else
    methos_and_path_.second = target_path;

  if (methos_and_path_.second.empty() && !cur_route_.autoindex)
    return (req_status_ = ER404);
  return CONTINUE;
}

handl_ret_codes Handler::query_parsing(const std::string &fo_pars) {
  if (body_parse)
    return body_parse(*this, fo_pars);
  header_part(fo_pars);
  handl_ret_codes tmp = route_searcher();
  if (tmp != CONTINUE)
    return (req_status_ = tmp);
  return is_recvest_rly_end(fo_pars);
}

handl_ret_codes Handler::is_recvest_rly_end(const std::string &fo_pars) {
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
  return (req_status_ = SUCCESSFUL);
}

handl_ret_codes Handler::parse_body_length(Handler &obj,
                                           const std::string &src) {
  if (src.size() - obj.position_ != obj.body_length_)
    return (obj.req_status_ = CONTINUE);
  obj.body_.append(src.substr(obj.position_, obj.body_length_));
  if (obj.max_body_ != -1 &&
      static_cast<int>(obj.body_.size()) > obj.max_body_) {
    obj.body_.resize(obj.max_body_);
    return (obj.req_status_ = ER413);
  }
  if (obj.body_.size() == obj.body_length_)
    return (obj.req_status_ = SUCCESSFUL);
  return (obj.req_status_ = CONTINUE);
};

handl_ret_codes Handler::parse_body_chunked(Handler &obj,
                                            const std::string &src) {
  if (src.substr(src.size() - strlen(parse_utils::query_end)) !=
      parse_utils::query_end)
    return (obj.req_status_ = CONTINUE);
  size_t tmp = obj.end_line(src, obj.position_);
  if (tmp == std::string::npos)
    return (obj.req_status_ = CONTINUE);
  std::string number(src.substr(obj.position_, tmp - obj.position_));
  if (!number.empty())
    obj.body_length_ = std::stoi(number, nullptr, 16);
  if (obj.body_length_ == 0) {
    obj.header_["CONTENT-LENGTH"] = std::to_string(obj.body_.size());
    return (obj.req_status_ = SUCCESSFUL);
  }
  obj.position_ = obj.next_line(src, obj.position_);
  obj.body_.append(src.substr(obj.position_, obj.body_length_));
  if (obj.max_body_ != -1 &&
      static_cast<int>(obj.body_.size()) > obj.max_body_) {
    obj.body_.resize(obj.max_body_);
    return (obj.req_status_ = ER413);
  }
  obj.position_ = obj.next_line(src, obj.position_);
  return parse_body_chunked(obj, src);
};

bool Handler::is_recvest_end(const std::string &fo_pars) const {
  if (end_block(fo_pars) != std::string::npos || body_parse)
    return true;
  return false;
}

connection  Handler::connection_type_prehandler() {
  map_str::iterator it = header_.find("CONNECTION-TYPE");
  if (it == header_.end()) {
    return CLOSE;
  }
  else {
    std::string upped;
    upped.resize(it->second.size());
    for (size_t i = 0; it->second[i]; ++i)
      upped[i] = std::toupper(it->second[i]);
    if (upped == "KEEP-ALIVE")
      return KEEP_ALIVE;
    else
      return CLOSE;
  }
}

bool Handler::create_response(std::list<std::vector<uint8_t>> &resp) {
  ResponseBuilder builder(
      config,
      t_request_data{header_, body_, cur_route_, methos_and_path_.second,
                     req_status_,
                     parse_utils::get_enum_methods(methos_and_path_.first),
                     query_string_, connection_type_prehandler()});
  connection connection_status = builder.build_response(resp);
  after_all();
  return static_cast<bool>(connection_status);
}

void Handler::after_all() {
  position_ = 0;
  body_length_ = 0;
  max_body_ = -1;
  header_.clear();
  methos_and_path_.first.clear();
  methos_and_path_.second.clear();
  query_string_.clear();
  body_.clear();
  req_status_ = SUCCESSFUL;
  body_parse = nullptr;
}

} // namespace http