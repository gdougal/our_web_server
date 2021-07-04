//
// Created by Lonmouth Mallador on 6/28/21.
//

#ifndef WEB_SERVER_AUTOINDEXRESONSEBUILDER_HPP
#define WEB_SERVER_AUTOINDEXRESONSEBUILDER_HPP

#include <string>
#include "ResponseBuilder.hpp"
#include "ConfigRepository.hpp"


class AutoindexResonseBuilder {
private:
    std::string generateDirLink(const std::string& dir_name,std::string&
                                                          index_dir,
                         const server_config&
                                                           serverConfig);
   std::string generateHead(const std::string& path);
   std::string generateEnd();

public:
  std::string build(const server_config& serverConfig, const std::string& path,
               const std::string& index_directory);
};

#endif // WEB_SERVER_AUTOINDEXRESONSEBUILDER_HPP
