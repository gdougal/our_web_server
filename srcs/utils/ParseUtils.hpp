//
// Created by Lonmouth Mallador on 6/30/21.
//
#pragma once
#include "manual_types.h"

namespace parse_utils {

static const char query_end[] = "\r\n\r\n";
static const char line_end[] = "\r\n";
static const char delim_method[] = " ";
static const char delim_base[] = " :";

static const char GET[] = "GET";
static const char POST[] = "POST";
static const char DELETE[] = "DELETE";
static const char HEAD[] = "HEAD";
static const char PUT[] = "PUT";
static const char cont_len[] = "CONTENT-LENGTH";
static const char encoding[] = "TRANSFER-ENCODING";
static const char chunked[] = "chunked";

methods									get_enum_methods(const std::string &method_str);
std::list<std::string>	getDirectoryList(const std::string& src);

} // namespace parse_utils

