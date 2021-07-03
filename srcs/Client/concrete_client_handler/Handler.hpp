#pragma once

#include <RouteEntity.hpp>
#include "manual_types.h"

using t_request_data = struct request_data;

namespace http {

class Handler : public BaseClientHandler<server_config, handl_ret_codes> {

  pair_str								pair_maker(const std::string &, const std::string &delim);
  void										header_part(const std::string &);
  size_t									next_line(const std::string &, size_t pos) const;
  size_t									end_line(const std::string &, size_t pos) const;
  size_t									end_block(const std::string &) const;
	std::string							search_file() const;
	handl_ret_codes					is_recvest_rly_end(const std::string &);
  static handl_ret_codes	parse_body_length(Handler &, const std::string &);  // length
  static handl_ret_codes	parse_body_chunked(Handler &, const std::string &); // chunk
  void after_all();

public:
	Handler() = delete;
  Handler(const server_config& cfg);
  virtual ~Handler();
  virtual bool							is_recvest_end(const std::string &) const;
  virtual handl_ret_codes		query_parsing(const std::string &);
  virtual const std::string	create_response();

  virtual void logger(const std::string &logs, int fd) const;

private:
  size_t								position_; // always start from end-line;
  int										body_length_;
  int										max_body_;
  map_str								header_;
  pair_str							methos_and_path_;
  std::string						body_;
	route									cur_route_;
	const server_config&	config;
	handl_ret_codes				req_status_;
	handl_ret_codes (*body_parse)(Handler &obj, const std::string &);
};
} // namespace http