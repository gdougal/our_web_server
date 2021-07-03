#pragma once

#include "manual_types.h"

using t_request_data = struct request_data;

namespace http {

class Handler : public BaseClientHandler<server_config> {

  pair_str pair_maker(const std::string &, const std::string &delim);
  void header_part(const std::string &);
  size_t next_line(const std::string &, size_t pos) const;
  size_t end_line(const std::string &, size_t pos) const;
  size_t end_block(const std::string &) const;
  bool is_recvest_rly_end(const std::string &);
  static bool parse_body_length(Handler &, const std::string &);  // length
  static bool parse_body_chunked(Handler &, const std::string &); // chunk
  void after_all();

public:
	Handler() = delete;
  Handler(const server_config& cfg);
  virtual ~Handler();
  virtual bool is_recvest_end(const std::string &) const;
  virtual bool query_parsing(const std::string &);
  virtual const std::string create_response();

  virtual void logger(const std::string &logs, int fd) const;

private:
  size_t position_; // always start from end-line;
  map_str header_;
  pair_str methos_and_path_;
  size_t body_length_;
  std::string body_;
	std::shared_ptr<t_request_data>	data_;
	const server_config& config;
  bool (*body_parse)(Handler &obj, const std::string &);
};
} // namespace http