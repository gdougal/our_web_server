//
// Created by Gilberto Dougal on 7/8/21.
//
#pragma once

template <typename data_type, typename query_status> class BaseClientHandler {
public:
  BaseClientHandler() {};
  BaseClientHandler(const data_type&) {};
  virtual query_status	query_parsing(const std::string &) = 0;
  virtual bool is_recvest_end(const std::string &) const = 0;
  virtual void create_response(std::list<std::vector<uint8_t>>&) = 0;
  virtual ~BaseClientHandler() = default;

  // отладочная
  virtual void logger(const std::string &logs, int fd) const {};
};

