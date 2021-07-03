//
// Created by Lonmouth Mallador on 6/29/21.
//

#include "ResponseUtils.hpp"
#include <fstream>
#include "CommonUtils.hpp"

namespace ResponseUtils {

	string read_from_file(const string& path_res) {
		ifstream page(PATH_TO_ROOT + path_res);
		string tmp;
		string body;
		while (std::getline(page, tmp)) {
			body += tmp;
		};
		return body;
	}

}