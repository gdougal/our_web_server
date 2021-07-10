//
// Created by Lonmouth Mallador on 7/6/21.
//

#include "CgiExecutor.hpp"
#include <CommonUtils.hpp>
#include "unistd.h"
#include "shared_ptr.hpp"
#include "iostream"
#include "fstream"
#include "ErrorBuilder.hpp"
#include "HeadersBuilder.hpp"

namespace {
const std::string SOFTWARE = "SERVER_SOFTWARE=GdougalLmalladoGdogeWebserv/1.0";
const std::string NAME = "SERVER_NAME=";
const std::string GATEWAY_INTERFACE = "GATEWAY_INTERFACE=CGI/1.0";
const std::string PROTOCOL_str = "SERVER_PROTOCOL=HTTP/1.1";
const std::string SERVER_PORT = "SERVER_PORT=";
const std::string REQUEST_METHOD = "REQUEST_METHOD=";
const std::string PATH_INFO = "PATH_INFO=";
const std::string PATH_TRANSLATED = "PATH_TRANSLATED=";
const std::string SCRIPT_NAME = "SCRIPT_NAME=";
const std::string QUERY_STRING = "QUERY_STRING=";
const std::string CONTENT_TYPE_str = "CONTENT_TYPE=";
const std::string CONTENT_LENGTH = "CONTENT_LENGTH=";
const std::string WTF_STRING = "HTTP_X_SECRET_HEADER_FOR_TEST=1";
} // namespace

namespace http {

std::list<std::string>
CgiExecutor::init_env(const t_request_data &data,
                      const server_config &serverConfig) {
  std::list<std::string> env;
  env.push_back("AUTH_TYPE=basic");
  env.push_back("REDIRECT_STATUS=200");
  env.push_back(SOFTWARE);
  env.push_back(NAME + serverConfig.host);
  env.push_back(GATEWAY_INTERFACE);
  env.push_back(PROTOCOL_str);
  env.push_back(SERVER_PORT + serverConfig.port);
  if (data.cur_method == methods::POST)
    env.push_back(REQUEST_METHOD + "POST");
  else if (data.cur_method == methods::DELETE)
    env.push_back(REQUEST_METHOD + "DELETE");
  env.push_back(PATH_INFO + "/directory/youpi.bla");
  env.push_back(PATH_TRANSLATED + PATH_TO_ROOT + "/cgi_tester");
  env.push_back(SCRIPT_NAME + "/directory/youpi.bla");
  env.push_back("SCRIPT_FILENAME=" + serverConfig.cgi_path);
  env.push_back(QUERY_STRING + data.query_string);
  env.push_back("REMOTE_ADDR=");
  env.push_back("REMOTE_IDENT=");
  env.push_back("REMOTE_USER=");
  env.push_back("REQUEST_URI=http://" + serverConfig.host + ":" +serverConfig
                                                                      .port +
                    + "/directory/youpi.bla");

  env.push_back(CONTENT_TYPE_str + data.header.find("CONTENT-TYPE")->second);
  env.push_back(CONTENT_LENGTH + ( (data.header.find("CONTENT-LENGTH") == data
.header.end() ? "0" : data.header.find("CONTENT-LENGTH")->second) ) );
  env.push_back(WTF_STRING);
  return env;
}

char **CgiExecutor::get_env(const t_request_data &data,
                            const server_config &serverConfig) {
  std::list<std::string> dirty_env = init_env(data, serverConfig);
  char** env(new char*[dirty_env.size() + 1]);
  std::list<std::string>::iterator first = dirty_env.begin();
  std::list<std::string>::iterator last = dirty_env.end();
  int i = 0;
  for (; first != last; first++, i++) {
    env[i] = new char[first->size() + 1];
    std::memcpy(env[i], first->c_str(), first->size());
    env[i][first->size()] = '\0';
  }
  env[dirty_env.size()] = NULL;
  return env;
}

#include <fcntl.h>

void CgiExecutor::build(const t_request_data &data,
                        const server_config &serverConfig,
                            std::list<std::vector<uint8_t>> &resp) {
  int fd = open("name", O_RDWR | O_TRUNC | O_CREAT, 0677);
  int fd1 = open("file", O_RDWR | O_TRUNC | O_CREAT, 0677);
  char **env = get_env(data, serverConfig);
  int pid;
  write(fd1, data.body.c_str(), data.body.size());
  lseek(fd1, 0, SEEK_SET);
  if ((pid = fork()) == -1)
    return /**/;
  if (!pid)
  {
    dup2(fd1, 0);
    dup2(fd, 1);
    char* argv[3];
    argv[0] = strdup("/Users/lmallado/our_web_server/cgi_tester");
    argv[1] = strdup("/Users/lmallado/our_web_server/cgi_tester");
    argv[2] = NULL;
    exit(execve(argv[0], argv, env) );
  }
  wait(NULL);
  lseek(fd, 0, SEEK_SET);
  struct stat s;
  fstat(fd, &s);
  std::string poluchenie;
  poluchenie.resize(s.st_size);
  read(fd, (void *)poluchenie.c_str(), s.st_size);
  size_t pos_var;
  if ((pos_var = poluchenie.find(parse_utils::query_end)) != std::string::npos)
    poluchenie = poluchenie.substr(pos_var + strlen(parse_utils::query_end));

  resp.push_back(std::vector<uint8_t>(poluchenie.begin(), poluchenie.end()));
  HeadersBuilder::build(R200, connection::KEEP_ALIVE, "text/html; "
                                                      "charset=utf-8",
                        poluchenie.size(),
                        serverConfig
                            .host,
                        serverConfig.port,
                        resp);
  resp.push_back(std::vector<uint8_t>(parse_utils::query_end,
parse_utils::query_end + 4));
  close(fd1);
  close(fd);
  for (int i = 0; env[i]; ++i)
    delete env[i];
//  delete env;
}

} // namespace http