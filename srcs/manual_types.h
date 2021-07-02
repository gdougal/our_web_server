//
// Created by gdougal on 22.06.2021.
//

#ifndef WEB_SERVER_MANUAL_TYPES_H
#define WEB_SERVER_MANUAL_TYPES_H

#include <list>
#include <map>
#include <string>
//#include <memory>
//#include "RouteEntity.hpp"
//#include "ConfigRepository.hpp"

class server_config;

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

enum methods: int { GET, POST, DELETE, HEAD, PUT, LAST_METH };
enum connection {KEEP_ALIVE, CLOSE};
enum content_type { HTML, CSS, JS, JPEG, PNG, BMP, UNDEFINED };

namespace http {
class Handler;
typedef std::map<std::string, std::string> map_str;
typedef std::pair<std::string, std::string> pair_str;

struct types {
  typedef http::Handler protocol;  // handler
  typedef server_config datatypes; // type of data
};
} // namespace http

template<typename T>
struct Optional_simple {

	bool is_val() const { return is_val_; }
	const T& get_or(const T& alt_ret) const {
		if (is_val_)
			return value_;
		return alt_ret;
	};

	void set_value(const T& value) {
		value_ = value;
		is_val_ = true;
	}
	Optional_simple(): is_val_(false) {};
	explicit Optional_simple(const T& value): is_val_(true), value_(value) {}
	Optional_simple(const Optional_simple<T>& ref) = default;
	Optional_simple& operator=(const Optional_simple<T>& ref)  = default;
	virtual ~Optional_simple() {}
private:
	bool	is_val_;
	T			value_;
};

typedef Optional_simple<std::string> OptStr;


#endif // WEB_SERVER_MANUAL_TYPES_H
