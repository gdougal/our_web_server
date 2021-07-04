//
// Created by Lonmouth Mallador on 6/28/21.
//

#include "AutoindexResonseBuilder.hpp"
#include <dirent.h>
#include <iostream>
#include <sstream>

std::string AutoindexResonseBuilder::build(const server_config &serverConfig,
                                      const std::string &path,
                                      const std::string &index_directory) {
  DIR *current_dir = opendir(path.c_str());
  std::string page = "";
  std::string index_dir_mutable = index_directory;
  page += generateHead(index_directory);
  for (struct dirent *dir = readdir(current_dir); dir;
       dir = readdir(current_dir)) {
    page += generateDirLink(string(dir->d_name), index_dir_mutable, serverConfig);
  }
  page += generateEnd();
  closedir(current_dir);
  return page;
}

std::string AutoindexResonseBuilder::generateHead(const std::string &path) {
  return "<html>"
         "<head>"
         "<title> autoindex </title>"
         "</head>"
         "<body>"
         "<h1> Index of " +
         path + "</h1><hr>";
}

std::string AutoindexResonseBuilder::generateEnd() {
  return "</body>"
         "</html>";
}

std::string
AutoindexResonseBuilder::generateDirLink(const std::string &dir_name,
                                         std::string &index_directory,
                                         const server_config &serverConfig) {
  stringstream ss;
  if (index_directory.c_str()[index_directory.length() - 1] != '/')
    index_directory += "/";
  ss << "<br><a href=\"http://" + serverConfig.host + ":" << serverConfig.port
     << index_directory + dir_name + "\">" + dir_name + "</a>";
  return ss.str();
}