//
// Created by Lonmouth Mallador on 6/28/21.
//
#pragma once

#include <string>
#include "ResponseBuilder.hpp"
#include "ConfigRepository.hpp"

namespace http {

  class AutoindexResonseBuilder {
  private:
    std::string generateDirLink(const std::string &dir_name,
                                std::string &index_dir,
                                const server_config &serverConfig);

    std::string generateHead(const std::string &path);

    std::string generateEnd();

  public:
    void build(const server_config &serverConfig, const std::string &path,
               const std::string &index_directory,
               std::list<std::vector<uint8_t> > &resp);
  };

}