//
// Created by Lonmouth Mallador on 6/28/21.
//

#include <dirent.h>
#include <sstream>
#include <iostream>
#include "AutoindexResonseBuilder.hpp"

string AutoindexResonseBuilder::build(server_config serverConfig, string path) {
    DIR *current_dir = opendir(path.c_str());
    for (struct dirent *dir = readdir(current_dir); dir; dir = readdir(current_dir)) {
        cout << "herre " << generateDirLink(string(dir->d_name), path, serverConfig) << endl;
    }
    closedir(current_dir);
    return std::string();
}

string
AutoindexResonseBuilder::generateDirLink(string const dir_name, std::string const &path, server_config serverConfig) {
    stringstream ss;
    ss << "\t\t<p><a href=\"http://" + serverConfig.host + ":" << \
        serverConfig.port << path + "/" + dir_name + "\">" + dir_name + "</a></p>\n";
    return ss.str();
}