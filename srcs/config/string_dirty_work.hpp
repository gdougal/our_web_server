//
// Created by Gilberto Dougal on 6/6/21.
//

#ifndef WEB_SERVER_STRING_DIRTY_WORK_HPP
#define WEB_SERVER_STRING_DIRTY_WORK_HPP
#include <iostream>
#include <map>

typedef std::map<std::string, std::string> map_str;
typedef std::pair<std::string, std::string> pair_str;

namespace string_dirty_work {
	size_t		next_line(const size_t& pos, const std::string& str, const std::string& end_line);
	pair_str	pair_maker(size_t& pos, const std::string& str, const std::string& mask, const std::string& end_line = std::string(""));
	size_t		get_string_map(map_str&	req_map, const std::string& str, const size_t pos, const std::string& mask, const std::string& end_line = std::string(""));
};


#endif //WEB_SERVER_STRING_DIRTY_WORK_HPP
