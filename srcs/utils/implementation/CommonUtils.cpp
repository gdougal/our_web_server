//
// Created by Gilberto Dougal on 7/3/21.
//
#include "CommonUtils.hpp"

req_file_status is_directory(const std::string &path) {
	struct stat s;
	std::string str = PATH_TO_ROOT + path;
	if (stat(str.c_str(), &s) == 0) {
		if (s.st_mode & S_IFDIR) {
			return IS_DIRECTORY;
		} else {
			return IS_FILE;
		}
	}
	return NOT_FOUND;
}