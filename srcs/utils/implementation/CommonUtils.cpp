//
// Created by Gilberto Dougal on 7/3/21.
//
#include "CommonUtils.hpp"

req_file_status is_directory(const std::string &path) {
        std::string cutted_path;
        if (path.c_str()[path.size() - 1] == '/')
          cutted_path = &path.c_str()[path.size() - 1];
        else
          cutted_path = path;
	struct stat s;
	std::string str = cutted_path;
	if (stat(str.c_str(), &s) == 0) {
		if (s.st_mode & S_IFDIR) {
			return IS_DIRECTORY;
		} else {
			return IS_FILE;
		}
	}
	return NOT_FOUND;
}