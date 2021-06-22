//
// Created by gdougal on 22.06.2021.
//

#ifndef WEB_SERVER_MANUAL_TYPES_H
#define WEB_SERVER_MANUAL_TYPES_H

struct Itypes {
	using protocol = std::nullptr_t; //handler
	using datatypes = std::nullptr_t; //type of data
};

struct http_types : public Itypes {
	using protocol = http::Handler; //handler
	using datatypes = server_config; //type of data
};

#endif //WEB_SERVER_MANUAL_TYPES_H
