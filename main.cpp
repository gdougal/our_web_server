#include "Server.hpp"
#include <csignal>
#include <iostream>
#include "Post.hpp"
#include "ConfigParser.hpp"

using std::string;
using std::list;

string configFileName = "config.wsc";

void pipe(int l) { sigignore(l); }
int main() {
  signal(SIGPIPE, pipe);
	std::list<std::shared_ptr<server_config> > config;
	ConfigParser parsed_struct(configFileName, {"server"}, {"error_pages", "routes"}, {"route"});
	for (size_t idx = 0; idx < parsed_struct.getContentCount(); ++ idx) {
		config.emplace_back(make_shared<server_config>(parsed_struct.getVarietyOfSection(idx)));
	}

  Server<http::types> serv(config);
  serv.run_server();
  return 0;
}