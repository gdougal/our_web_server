#pragma once

#include <algorithm>
#include <filesystem>
#include <sys/stat.h>


template<class Container, typename t_element>
bool find_some(const Container& cont, const t_element& elem) {
	if (std::find(cont.begin(), cont.end(), elem) != cont.end())
		return true;
	return false;
}


enum req_file_status { IS_FILE, IS_DIRECTORY, NOT_FOUND };
req_file_status			is_directory(const std::string &path);
