//
// Created by gdougal on 22.06.2021.
//

#ifndef WEB_SERVER_MANUAL_TYPES_H
#define WEB_SERVER_MANUAL_TYPES_H


struct Itypes {
	typedef std::nullptr_t protocol; //handler
	typedef std::nullptr_t datatypes; //type of data
};

template <typename data_type>
class BaseClientHandler {
public:
		virtual bool							      query_parsing(const std::string &) = 0;
		virtual bool							      is_recvest_end(const std::string &) const = 0;
		virtual const std::string				create_response(const data_type& data) = 0;
		virtual ~BaseClientHandler() = default;

		// отладочная
		virtual void logger(const std::string &logs, int fd) const = 0;
};

namespace http {
		class Handler;
		typedef std::map<std::string, std::string> map_str;
		typedef std::pair<std::string, std::string> pair_str;

		struct types : public Itypes {
				typedef http::Handler protocol; //handler
				typedef server_config datatypes; //type of data
		};
}

#endif //WEB_SERVER_MANUAL_TYPES_H
