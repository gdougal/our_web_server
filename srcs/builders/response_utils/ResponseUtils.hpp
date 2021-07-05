//
// Created by Lonmouth Mallador on 6/29/21.
//

#ifndef WEB_SERVER_RESPONSEUTILS_HPP
#define WEB_SERVER_RESPONSEUTILS_HPP

#include <string>
#include "list"

namespace ResponseUtils {

	void read_from_file(const std::string& path_res, std::list<std::vector<uint8_t> >&);
	std::string get_content_type(const std::string& filename);

}
#endif // WEB_SERVER_RESPONSEUTILS_HPP
