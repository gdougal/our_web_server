#include <csignal>
#include "Server.hpp"
#include "shared_ptr.hpp"
#include "set"
#include "i_wanna_range_based_for.hpp"


std::string configFileName = "config.wsc";

void pipe(int l) { sigignore(l); }

std::list<ft::shared_ptr<http::server_config> > init() {
  typedef std::list<ft::shared_ptr<http::server_config> > serv_cfgs;
  serv_cfgs config;
  ConfigParser parsed_struct(configFileName, {"server"}, {"error_pages", "routes"}, {"route"});
  for (size_t idx = 0; idx < parsed_struct.getContentCount(); ++ idx) {
    config.push_back(new http::server_config(parsed_struct.getVarietyOfSection(idx)) );
  }

  if (config.empty())
    throw std::logic_error("Config empty!");
  std::set<std::string> port_checker;
  AUTO_FOR(serv_cfgs::iterator, iter, config) {
    std::string val = iter->get()->port;
    if (val.empty() || iter->get()->host.empty())
      throw std::logic_error("Need to port and host value in config-file");
    if(port_checker.find(val) != port_checker.end())
      throw std::logic_error("Duplicate port value in config-file");
    if (iter->get()->path_to_root.empty())
      throw std::logic_error("Path to the root needed");
    if (iter->get()->routes.empty())
      throw std::logic_error("Haven`t route");
    port_checker.insert(val);
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