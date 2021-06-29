//
// Created by Lonmouth Mallador on 6/28/21.
//

#ifndef WEB_SERVER_AUTOINDEXRESONSEBUILDER_HPP
#define WEB_SERVER_AUTOINDEXRESONSEBUILDER_HPP

#include <string>
#include "ResponseBuilder.hpp"

using namespace std;

class AutoindexResonseBuilder {
private:
    string  generateDirLink(string const dir_name, std::string const &path, server_config serverConfig);
    string generateLinks();
    string generateHead();
    string generateEnd();
public:
  string build(server_config serverConfig, string path);
};

#endif // WEB_SERVER_AUTOINDEXRESONSEBUILDER_HPP
