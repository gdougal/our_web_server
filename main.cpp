#include "Server.hpp"
#include <csignal>
#include <iostream>

void pipe(int l) { sigignore(l); }

int main() {
  signal(SIGPIPE, pipe);
  // TODO: Thies piece of data should filling by parsing part
  std::list<route> routes;
  std::list<methods> allowed_methods;
  allowed_methods.push_back(methods(GET));
  allowed_methods.push_back(methods(HEAD));
  routes.push_back(route("/", "direction", false, "/pages/simple.html",
                         "/pages/lyubaya.html", "/pages/lyubaya.html",
                         allowed_methods));
  std::map<int, std::string> error_page;
  error_page.insert(std::make_pair(1, "/pages/simple"));
  server_config serverConfig("127.0.0.1", "8000", "lol", 21, error_page,
                             routes);
  // TODO: Thies piece of data should filling by parsing part

  std::list<server_config> cfgs;
  cfgs.emplace_back(serverConfig);

  Server<http::types> serv(cfgs);
  serv.run_server();
  return 0;
}
