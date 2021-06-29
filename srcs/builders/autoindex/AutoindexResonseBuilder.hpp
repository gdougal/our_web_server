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
    string generateDirLink(string dir_name, string path, server_config
                                                           serverConfig);
    string generateHead(string path);
    string generateEnd();

public:
  string build(server_config serverConfig, string path, string index_directory);
};

#endif // WEB_SERVER_AUTOINDEXRESONSEBUILDER_HPP
