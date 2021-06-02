#include <iostream>
#include "Server.hpp"

int main()
{
	std::string path("./config.txt");
	std::shared_ptr<Server> serv(new Server(Config(path)));
	serv->run_server();
	return 0;
}
