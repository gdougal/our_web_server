//
// Created by Lonmouth Mallador on 6/28/21.
//

#include "AutoindexResonseBuilder.hpp"
#include <dirent.h>
#include <iostream>
#include <sstream>

string AutoindexResonseBuilder::build(server_config serverConfig, string path,
                                      string index_directory) {
  DIR *current_dir = opendir(path.c_str());
  string page = "";
  page += generateHead(index_directory);
  for (struct dirent *dir = readdir(current_dir); dir;
       dir = readdir(current_dir)) {
    page += generateDirLink(string(dir->d_name), index_directory, serverConfig);
  }
  page += generateEnd();
  closedir(current_dir);
  return page;
}

string AutoindexResonseBuilder::generateHead(string path) {
  return "<html>"
         "<head>"
         "<title> autoindex </title>"
         "</head>"
         "<body>"
         "<h1> Index of " +
         path + "</h1>";
}

string AutoindexResonseBuilder::generateEnd() {
  return "</body>"
         "</html>";
}

string AutoindexResonseBuilder::generateDirLink(string dir_name, string
                                                                     index_directory,
                                                server_config serverConfig) {
  stringstream ss;
  ss << "<p><a href=\"http://" + serverConfig.host + ":" << serverConfig.port
     <<  index_directory + dir_name + "\">" + dir_name + "</a></p>";
  return ss.str();
}