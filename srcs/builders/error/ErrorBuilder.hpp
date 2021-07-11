//
// Created by Lonmouth Mallador on 6/30/21.
//
#pragma once

#include "ConfigRepository.hpp"
#include <string>

namespace http {

static const std::string PATH_TO_ERROR_PAGES = "/default_error_pages/";
static const std::map<handl_ret_codes, std::string> default_error_pages = {
    {ER400, PATH_TO_ERROR_PAGES + "400.html"},
    {ER404, PATH_TO_ERROR_PAGES + "404.html"},
    {ER403, PATH_TO_ERROR_PAGES + "403.html"},
    {ER405, PATH_TO_ERROR_PAGES + "405.html"},
    {ER413, PATH_TO_ERROR_PAGES + "413.html"},
    {ER500, PATH_TO_ERROR_PAGES + "500.html"}};

class ErrorBuilder {
private:
public:
  static void build(handl_ret_codes error_code, server_config serverConfig,
                    std::list<std::vector<uint8_t>> &);
};

} // namespace http
