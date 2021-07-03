//
// Created by gdougal on 22.06.2021.
//

#ifndef WEB_SERVER_MANUAL_TYPES_H
#define WEB_SERVER_MANUAL_TYPES_H

#include <list>
#include <map>
#include <string>


class server_config;

template <typename data_type, typename query_status> class BaseClientHandler {
public:
	BaseClientHandler() {};
	BaseClientHandler(const data_type&) {};
  virtual query_status	query_parsing(const std::string &) = 0;
  virtual bool is_recvest_end(const std::string &) const = 0;
  virtual const std::string create_response() = 0;
  virtual ~BaseClientHandler() = default;

  // отладочная
  virtual void logger(const std::string &logs, int fd) const = 0;
};

enum methods: int { GET, POST, DELETE, HEAD, PUT, LAST_METH };
enum connection {KEEP_ALIVE, CLOSE};
enum content_type { HTML, CSS, JS, JPEG, PNG, BMP, UNDEFINED };
enum handl_ret_codes: int { ER400 = 400, ER404 = 404, ER403 = 403, ER405 = 405, ER413 = 413, CONTINUE = 1, SUCCESSFUL = 0 };

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

template<typename T>
struct Optional_simple {

	bool is_val() const { return is_val_; }
	const T& get_or(const T& alt_ret) const {
		if (is_val_)
			return value_;
		return alt_ret;
	};

	const T& get() const {
		return value_;
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
