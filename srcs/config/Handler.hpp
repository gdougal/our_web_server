//
// Created by Gilberto Dougal on 6/6/21.
//

#ifndef WEB_SERVER_HANDLER_HPP
#define WEB_SERVER_HANDLER_HPP
#include <iostream>
#include <map>
#include <unistd.h>

class BaseClientHandler {
public:
	virtual bool							query_parsing(const std::string &) = 0;
	virtual bool							is_recvest_end(const std::string &) const = 0;
	virtual const std::string	create_response() = 0;
	virtual ~BaseClientHandler() = default;

	// отладочная
	virtual void logger(const std::string &logs, int fd) const = 0;
};

namespace http {

	typedef std::map<std::string, std::string> map_str;
	typedef std::pair<std::string, std::string> pair_str;

	class Handler : public BaseClientHandler {

		pair_str			pair_maker(const std::string& , const std::string &delim);
		void					header_part(const std::string&);
		size_t				next_line(const std::string& , size_t pos)	const;
		size_t				end_line(const std::string& , size_t pos)		const;
		size_t				end_block(const std::string& )				const;

		bool					is_recvest_rly_end(const std::string& );
		static bool		parse_body_length(Handler& , const std::string& );	// length
		static bool		parse_body_chunked(Handler& , const std::string& );	// chunk
		void					after_all();

	public:
		/*construct*/							Handler();
		virtual										~Handler();

		virtual				bool				is_recvest_end(const std::string& )	const;
		virtual				bool				query_parsing(const std::string& );
		virtual const	std::string	create_response();

		virtual void logger(const std::string &logs, int fd) const {
			write(fd, logs.data(), logs.size());
			write(fd, "\n", 1);
			write(fd, "Key: ", 5);
			write(fd, methos_and_path_.first.data(), methos_and_path_.first.size());
			write(fd, " Value: ", 8);
			write(fd, methos_and_path_.second.data(), methos_and_path_.second.size());
			write(fd, "\n", 1);
			for (auto iter = query_.begin(); iter != query_.end(); ++iter) {
				write(fd, "Key: ", 5);
				write(fd, iter->first.data(), iter->first.size());
				write(fd, " Value: ", 8);
				write(fd, iter->second.data(), iter->second.size());
				write(fd, "\n", 1);
			}
		}

	private:
		size_t			position_; // always start from end-line;
		map_str			query_;
		pair_str		methos_and_path_;
		size_t			body_length_;
		std::string	body_;
		bool (*body_parse)(Handler& obj, const std::string&);
	};
}


#endif //WEB_SERVER_HANDLER_HPP