#pragma once

#include <algorithm>
#include <filesystem>
#include <sys/stat.h>

static const std::string PATH_TO_ROOT =
    "/Users/lmallado/our_web_server";

template<class Container, typename t_element>
bool find_some(const Container& cont, const t_element& elem) {
	if (std::find(cont.begin(), cont.end(), elem) != cont.end())
		return true;
	return false;
}

template<typename type, typename e_type>
inline e_type to_enum(type val) {
	return static_cast<e_type>(val);
}

enum req_file_status { IS_FILE, IS_DIRECTORY, NOT_FOUND };
req_file_status			is_directory(const std::string &path);
