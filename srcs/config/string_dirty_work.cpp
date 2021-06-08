//
// Created by Gilberto Dougal on 6/6/21.
//

#include "string_dirty_work.hpp"

namespace string_dirty_work {


	size_t	next_line(const size_t& pos, const std::string& str, const std::string& end_line) {
		size_t next_line = str.find_first_of(end_line, pos);
		next_line += end_line.size();
		return next_line;
	}

	pair_str	pair_maker(size_t& pos, const std::string& str, const std::string& mask, const std::string& end_line) {
		size_t end_first = str.find_first_of(mask, pos);
		size_t start_second = str.find_first_not_of(mask, end_first);
		size_t end_second;
		if (!end_line.empty())
			end_second = str.find_first_of(end_line, start_second);
		else
			end_second = str.find_first_of(mask, start_second);

		if (end_first == str.npos || start_second == str.npos || end_second == str.npos) {
			pos = str.npos;
			return pair_str();
		}
		std::string key(str.data() + pos, end_first - pos);
		std::string value(str.data() + start_second, end_second - start_second);
		pair_str insert_pair(key, value);
		pos = next_line(end_second, str, end_line);
		return insert_pair;
	}
//	"POST /asdfaf/?1=1_&2=2_&3=3_ HTTP/1.1\r\nContent-Type: multipart/form-data; boundary=--------------------------127545439466991343653611\r\ncache-control: no-cache\r\nPostman-Token: 0920aadf-0833-411d-ac14-333e7e5da404\r\nUser-Agent: PostmanRuntime/7.3.0\r\nAccept: */*\r\nHost: 127.0.0.1:8000\r\naccept-encoding: gzip, deflate\r\ncontent-length: 371\r\nConnection: keep-alive\r\n\r\n----------------------------127545439466991343653611\r\nContent-Disposition: form-data; name=\"qqe\"\r\n\r\nqwe"
	size_t		get_string_map(map_str&	req_map, const std::string& str, size_t pos, const std::string& mask, const std::string& end_line) {
		pair_str insert_pair(pair_maker(pos, str, mask, end_line));
		if (!insert_pair.first.empty())
			req_map.insert(insert_pair);
		return pos;
	}
};