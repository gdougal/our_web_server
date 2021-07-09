//
// Created by Gilberto Dougal on 6/29/21.
//

#pragma once
#include "manual_types.h"
#include <map>
#include <string>
#include "RouteEntity.hpp"

namespace http {

  typedef struct request_data {
    const http::map_str &header;
    const std::string &body;
    const route &request_route;
    const std::string &path;
    const handl_ret_codes code;
    const methods cur_method;
  } t_request_data;

}