//
// Created by Lonmouth Mallador on 7/6/21.
//

#include "CgiExecutor.hpp"

//void CgiExecutor::init_env(std::list<std::string> &env,
//                           const t_request_data &data, const route &route,
//                           const server_config &serverConfig) {
//  env.push_back(SOFTWARE);
//  env.push_back(NAME + serverConfig.host);
//  env.push_back(GATEWAY_INTERFACE);
//  env.push_back(PROTOCOL);
//  env.push_back(SERVER_PORT + serverConfig.port);
//  if (data.cur_method == methods::POST)
//    env.push_back(REQUEST_METHOD + "POST");
//  if (data.cur_method == methods::DELETE)
//    env.push_back(REQUEST_METHOD + "DELETE");
//  env.push_back(PATH_INFO + PATH_TO_ROOT + serverConfig.cgi_path);
//  env.push_back(PATH_TRANSLATED + PATH_TO_ROOT + serverConfig.cgi_path);
//  env.push_back(SCRIPT_NAME + serverConfig.cgi_path);
//  env.push_back(QUERY_STRING); //Нужно добавить
//  env.push_back(CONTENT_TYPE + data.header.find("CONTENT-TYPE")->second);
//  env.push_back(CONTENT_TYPE + data.header.find("CONTENT-LENGTH")->second);
//}
//
//void CgiExecutor::build(const t_request_data &data,
//                        const server_config &serverConfig, const route &route,
//                        std::list<std::vector<uint8_t>> &) {
//
//}
