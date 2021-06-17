#include <iostream>
#include "Server.hpp"
#include <csignal>


void pipe(int l) {
	sigignore(l);
}


int main()
{
	signal(SIGPIPE, pipe);
	std::string path("./config.txt");
	std::shared_ptr<Server<http::Handler> > serv(new Server<http::Handler>(Config(path)));
	serv->run_server();
	return 0;
}
