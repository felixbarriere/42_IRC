#include "../../inc/utils.hpp"

void	user(Server *server, Client *client) {
	(void) server;
	std::cout << "DEBUG ===> USER function called"  << std::endl << std::endl;
	client->setUser(client->getMessage()->getParams()[0]);
}
