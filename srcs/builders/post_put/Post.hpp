//
// Created by Gilberto Dougal on 6/29/21.
//

#ifndef WEB_SERVER_POST_HPP
#define WEB_SERVER_POST_HPP
#include "ResponseBuilder.hpp"


class Post {
private:

public:
	Post() = delete;
	Post(const Post &ref) = delete;
	Post &operator=(const Post &ref) = delete;
//	static const std::string	put(const pair<std::string, std::string>&, );
	virtual ~Post() {};
};


#endif //WEB_SERVER_POST_HPP
