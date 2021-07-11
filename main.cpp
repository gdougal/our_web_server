#include <csignal>
#include "Server.hpp"
#include "shared_ptr.hpp"
#include "set"


std::string configFileName = "config.wsc";

void pipe(int l) { sigignore(l); }

std::list<ft::shared_ptr<http::server_config> > init() {
  std::list<ft::shared_ptr<http::server_config> > config;
  ConfigParser parsed_struct(configFileName, {"server"}, {"error_pages", "routes"}, {"route"});
  std::set<std::string> port_checker;
  for (size_t idx = 0; idx < parsed_struct.getContentCount(); ++ idx) {
    std::string val = (parsed_struct.getVarietyOfSection(idx))["server"].getStrValue("port");
    if ( parsed_struct.getVarietyOfSection(idx).find("routes") == parsed_struct.getVarietyOfSection(idx).end() )
      throw std::logic_error("Need to routes field");
    if (val.empty())
      throw std::logic_error("Need to port value in config-file");
    if(port_checker.find(val) != port_checker.end())
      throw std::logic_error("Duplicate port value in config-file");
    port_checker.insert(val);
    config.push_back(new http::server_config(parsed_struct.getVarietyOfSection(idx)) );
  }
  signal(SIGPIPE, pipe);
  return config;
}

int main() {
  std::list<ft::shared_ptr<http::server_config> > config;
  try {
    config = init();
  }
  catch (std::exception& a) {
    std::cout << a.what() << std::endl;
    exit(-1);
  }
  try {
    Server<http::types> serv(config);
    serv.run_server();
  }
  catch (std::exception& a) {
    std::cout << a.what() << std::endl;
    exit(-1);
  }
  return 0;
}