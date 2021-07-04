//
// Created by Gilberto Dougal on 6/29/21.
//

#ifndef WEB_SERVER_POST_HPP
#define WEB_SERVER_POST_HPP
#include "ResponseBuilder.hpp"
#include "fstream"


class Post {
private:

	Post() = delete;
	Post(const Post &ref) = delete;
	Post &operator=(const Post &ref) = delete;
public:
	static const int	put(const std::string& filename, const t_request_data& data) {
		std::ofstream	outfile;
		outfile.open( filename.c_str() );
		if (outfile.is_open()) {
			outfile.write(data.body.c_str(), data.body.size());
			return HeadersBuilder::build(204,
																	 (data.header.find("CONNECTION-TYPE")->second == KEEP_ALIVE_STR),
																	 (),
																	 data.body.size() ); //204; // TODO: will call headerBuildr and
                                    // return std::string
		}
		else {
			outfile.open(filename.c_str());
			outfile.write(data.body.c_str(), data.body.size());
			return 201;
		}
	};

	virtual ~Post() {};
};


#endif //WEB_SERVER_POST_HPP
