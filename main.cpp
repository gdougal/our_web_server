#include <iostream>
#include "Server.hpp"
#include <csignal>


void pipe(int l) {
	sigignore(l);
}


int main()
{
	std::list<route> routes;
	std::list<methods> allowed_methods;
	allowed_methods.push_back(methods(GET));
	allowed_methods.push_back(methods(HEAD));
	routes.push_back(route("/", false, "/pages/simple.html", "/pages/lyubaya.html",
												 "/pages/lyubaya.html", allowed_methods));
	server_config serverConfig("127.0.0.1", "8000", "lol", 21,
														 "/pages/simple"
														 ".html", routes);
	signal(SIGPIPE, pipe);
	std::string path("./config.txt");
	std::list<server_config> cfgs;
	cfgs.emplace_back(serverConfig);
	Server<http::Handler, server_config> serv(cfgs);
	serv.run_server();
	return 0;
}
