//
// Created by gdougal on 22.06.2021.
//

#ifndef WEB_SERVER_MANUAL_TYPES_H
#define WEB_SERVER_MANUAL_TYPES_H

#include <list>
#include <map>
#include "RouteEntity.hpp"
#include "ConfigRepository.hpp"


template <typename data_type> class BaseClientHandler {
public:
	BaseClientHandler() {};
	BaseClientHandler(const data_type&) {};
  virtual bool query_parsing(const std::string &) = 0;
  virtual bool is_recvest_end(const std::string &) const = 0;
  virtual const std::string create_response() = 0;
  virtual ~BaseClientHandler() = default;

  // отладочная
  virtual void logger(const std::string &logs, int fd) const = 0;
};

namespace http {
class Handler;
typedef std::map<std::string, std::string> map_str;
typedef std::pair<std::string, std::string> pair_str;

struct types {
  typedef http::Handler protocol;  // handler
  typedef server_config datatypes; // type of data
};
} // namespace http

#endif // WEB_SERVER_MANUAL_TYPES_H
