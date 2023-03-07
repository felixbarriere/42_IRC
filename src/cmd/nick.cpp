#include "../../inc/utils.hpp"

void	nick(Server *server, Client *client) {
	(void) server;
	std::cout << "DEBUG ===> NICK function called"  << std::endl << std::endl;

	// check command syntax

	std::cout << "DEBUG ===> params[0]: " << client->getMessage()->getParams()[0] << std::endl << std::endl;
	client->setNick(client->getMessage()->getParams()[0]);
	std::cout << "DEBUG ===> client->getNick(): " << client->getNick() << std::endl << std::endl;

	// utiliser send pour indiquer au client que le nickname à changé 

}
