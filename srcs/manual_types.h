//
// Created by gdougal on 22.06.2021.
//

#ifndef WEB_SERVER_MANUAL_TYPES_H
#define WEB_SERVER_MANUAL_TYPES_H

#include <list>
#include <map>
#include <string>


class server_config;

enum methods: int {
	GET,
	POST,
	DELETE,
	HEAD,
	PUT,
	LAST_METH
};


enum connection: bool {
	KEEP_ALIVE = true,
	CLOSE = false
};

enum handl_ret_codes: int {
	R100 = 100,
	R200 = 200,
	R201 = 201,
	ER204 = 204,
	ER400 = 400,
	ER403 = 403,
	ER404 = 404,
	ER405 = 405,
	ER413 = 413,
	ER500 = 500,
	CONTINUE = 1,   //обязательные поля
	SUCCESSFUL = 0    //обязательные поля
};

template <typename data_type, typename query_status> class BaseClientHandler {
public:
	BaseClientHandler() {};
	BaseClientHandler(const data_type&) {};
  virtual query_status	query_parsing(const std::string &) = 0;
  virtual bool is_recvest_end(const std::string &) const = 0;
  virtual const void create_response(std::list<std::vector<uint8_t>>&) = 0;
  virtual ~BaseClientHandler() = default;

  // отладочная
  virtual void logger(const std::string &logs, int fd) const = 0;
};

namespace http {

class Handler;
typedef std::map<std::string, std::string> map_str;
typedef std::pair<std::string, std::string> pair_str;

struct types {
  typedef	Handler	protocol;  // handler
  typedef	server_config	datatypes; // type of data
  typedef	handl_ret_codes ret_codes;
};

} // namespace http


#endif // WEB_SERVER_MANUAL_TYPES_H
