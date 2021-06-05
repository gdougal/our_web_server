#include <iostream>
#include "Server.hpp"


void pipe(int l) {
	sigignore(l);
}

int main()
{
	signal(SIGPIPE, pipe);
	std::string path("./config.txt");
	std::shared_ptr<Server> serv(new Server(Config(path)));
	serv->run_server();
	return 0;
}
