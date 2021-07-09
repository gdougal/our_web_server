#include <csignal>
#include "Server.hpp"
#include "shared_ptr.hpp"


std::string configFileName = "config.wsc";

void pipe(int l) { sigignore(l); }

std::list<ft::shared_ptr<http::server_config> > init() {
  std::list<ft::shared_ptr<http::server_config> > config;
  ConfigParser parsed_struct(configFileName, {"server"}, {"error_pages", "routes"}, {"route"});
  for (size_t idx = 0; idx < parsed_struct.getContentCount(); ++ idx) {
    config.push_back(new http::server_config(parsed_struct.getVarietyOfSection(idx)) );
  }
  return config;
}

int main() {
  signal(SIGPIPE, pipe);
  std::list<ft::shared_ptr<http::server_config> > config(init());

  Server<http::types> serv(config);
  serv.run_server();
  return 0;
}