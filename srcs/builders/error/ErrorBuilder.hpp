//
// Created by Lonmouth Mallador on 6/30/21.
//

#ifndef WEB_SERVER_ERRORBUILDER_HPP
#define WEB_SERVER_ERRORBUILDER_HPP

#include "ConfigRepository.hpp"
#include "ResponseUtils.hpp"
#include <string>

using namespace std;

static const string PATH_TO_ERROR_PAGES = "/default_error_pages/";
static const map<int, string> default_error_pages = {
    {400, PATH_TO_ERROR_PAGES + "400.html"},
    {404, PATH_TO_ERROR_PAGES + "404.html"},
    {403, PATH_TO_ERROR_PAGES + "403.html"},
    {405, PATH_TO_ERROR_PAGES + "405.html"},
    {413, PATH_TO_ERROR_PAGES + "413.html"},
    {500, PATH_TO_ERROR_PAGES + "500.html"}
    };

class ErrorBuilder {
private:
public:
  static string build(const int &error_code, server_config serverConfig);
};

#endif // WEB_SERVER_ERRORBUILDER_HPP
