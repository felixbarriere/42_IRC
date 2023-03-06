#include "../../inc/utils.hpp"

void	nick(Server *server, Client *client) {
	(void) server;
	std::cout << "DEBUG ===> NICK function called"  << std::endl << std::endl;
	client->setNick(client->getMessage()->getParams()[0]);
}
