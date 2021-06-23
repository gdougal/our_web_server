//
// Created by gdougal on 22.06.2021.
//

#ifndef WEB_SERVER_MANUAL_TYPES_H
#define WEB_SERVER_MANUAL_TYPES_H


struct Itypes {
	typedef std::nullptr_t protocol; //handler
	typedef std::nullptr_t datatypes; //type of data
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
