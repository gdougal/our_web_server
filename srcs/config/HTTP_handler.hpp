//
// Created by Gilberto Dougal on 6/6/21.
//

#ifndef WEB_SERVER_HTTP_HANDLER_HPP
#define WEB_SERVER_HTTP_HANDLER_HPP
#include <iostream>
#include <map>
#include <fstream>
#include <unistd.h>

typedef std::map<std::string, std::string> map_str;
typedef std::pair<std::string, std::string> pair_str;

class BaseClientHandler {
public:
	virtual void							operator()(const std::string&) {};
	virtual bool							is_recvest_end(const std::string&) const = 0;
	virtual const	std::string	create_response() const = 0;
	virtual ~BaseClientHandler() {}
	// отладочная
	virtual void	logger(const std::string& logs, int fd) const = 0;
};

class BasicRequestHandler {
public:
	BasicRequestHandler() {};
};

namespace http {
	static const char	query_end[] = "\r\n\r\n";
	static const char	line_end[] = "\r\n";
	static const char	delim_method[] = " ";
	static const char	delim_base[] = " :";
	static const char request_init[] = "HTTP/1.1 200 OK\r\nVersion: HTTP/1.1\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: ";
	static const char bad_request[] = "HTTP/1.1 400 Bad Request\r\nServer: abracadabra\r\nContent-Type: text/html\r\nContent-Length: 126\r\nConnection: close\r\n\r\n";
}

class GetHandler : public BasicRequestHandler {

};

class PostHandler : public BasicRequestHandler {

};

class DeleteHandler : public BasicRequestHandler {

};

class HTTP_handler: public BaseClientHandler {

	pair_str	pair_maker(const std::string& fo_pars, const std::string& delim);
	void			get_string_map(const std::string& fo_pars);
	void			query_parsing(const std::string& fo_pars);
	void			header_parse(const std::string& fo_pars, size_t end_block);
	size_t		next_line(const std::string& fo_pars, size_t pos)	const;
	size_t		end_line(const std::string& fo_pars, size_t pos)	const;
	size_t		end_block(const std::string& fo_pars)							const;
public:
	HTTP_handler();
	virtual ~HTTP_handler();
	virtual void	operator()(const std::string& fo_pars) { query_parsing(fo_pars); }
	virtual bool	is_recvest_end(const std::string& fo_pars) const;
	virtual const std::string create_response() const;

	virtual void		logger(const std::string& logs, int fd) const {
		write(fd, logs.data(), logs.size());
		write(fd, "Key: ", 5);
		write(fd, methos_and_path_.first.data(), methos_and_path_.first.size());
		write(fd, " Value: ", 8);
		write(fd, methos_and_path_.second.data(), methos_and_path_.second.size());
		write(fd, "\n", 1);
		for(auto iter = query_.begin(); iter != query_.end(); ++iter) {
			write(fd, "Key: ", 5);
			write(fd, iter->first.data(), iter->first.size());
			write(fd, " Value: ", 8);
			write(fd, iter->second.data(), iter->second.size());
			write(fd, "\n", 1);
		}
	}

private:
	size_t		position_; // always start from end-line;
	map_str		query_;
	pair_str	methos_and_path_;
};


#endif //WEB_SERVER_HTTP_HANDLER_HPP