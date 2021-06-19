//
// Created by Gilberto Dougal on 6/14/21.
//

#ifndef WEB_SERVER_HTTP_STUFF_HPP
#define WEB_SERVER_HTTP_STUFF_HPP

#include <map>
#include <fstream>

namespace http {

	typedef std::map<std::string, std::string> map_str;
	typedef std::pair<std::string, std::string> pair_str;


	namespace query_type {
		static const char	GET[] = "GET";
		static const char	POST[] = "POST";
		static const char	DELETE[] = "DELETE";
		static const char	HEAD[] = "HEAD";
	}

	namespace header {
			static const char cont_len[] = "CONTENT-LENGTH";
			static const char encoding[] = "TRANSFER-ENCODING";
			static const char chunked[] = "chunked";
	}

	static const char	query_end[] = "\r\n\r\n";
	static const char	line_end[] = "\r\n";
	static const char	delim_method[] = " ";
	static const char	delim_base[] = " :";
	static const char request_init[] = "HTTP/1.1 200 OK\r\nVersion: HTTP/1.1\r\nConnection: keep-alive\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: ";
	static const char bad_request[] = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\n"; /* Server: abracadabra\r\nContent-Type: text/html\r\nContent-Length: 126\r\n */

	static void GET(std::string& response, const map_str& header, const pair_str& path) {
		std::ifstream page("/Users/gdougal/Desktop/our_web_server" + path.second);
//    std::ifstream page("/home/local/REGION/as.doynikov/clion_pj/hm" + path.second);
		std::string body;
		std::string tmp;
		while (std::getline(page, tmp)) {
			body += tmp;
		};
		response = http::request_init + std::to_string(body.length()) + http::query_end + body;
	};

	static void POST(std::string& response, const map_str& header, const pair_str& path) {
		response = "Я не ебу, что делать";
		std::cout << response << std::endl;
	};

	static void DELETE(std::string& response, const map_str& header, const pair_str& path) {
		response = "Я тоже не ебу, что делать";
		std::cout << response << std::endl;
	};

	static void HEAD(std::string& response, const map_str& header, const pair_str& path) {
		response = "Я тоже не ебу, что делать";
		std::cout << response << std::endl;
	};



	namespace {
		typedef void (t_f)(std::string&, const map_str&, const pair_str&);
		struct functor {
			t_f *function;
			void operator()(std::string& response, const map_str& header, const pair_str& path) const { (*function)(response, header, path); };
			explicit functor(t_f *function) : function(function) {}
		};

		static std::map<std::string, functor> initialize() {
			std::map<std::string, functor> init_methods;
			init_methods.insert(std::pair<std::string, functor>(query_type::GET, functor(GET)) );
			init_methods.insert(std::pair<std::string, functor>(query_type::POST, functor(POST)) );
			init_methods.insert(std::pair<std::string, functor>(query_type::DELETE, functor(DELETE)) );
			init_methods.insert(std::pair<std::string, functor>(query_type::HEAD, functor(HEAD)) );
			return init_methods;
		}
	}

	static const std::map<std::string, functor> methods(initialize());
}


#endif //WEB_SERVER_HTTP_STUFF_HPP
