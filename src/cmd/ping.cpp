#include "../../inc/utils.hpp"

void	ping(Server *server, Client *client) {
	(void)server;
	(void)client;
	if (client->getWelcome() == false)
		return ;


	client->sendMsg("PONG " + client->getMessage()->getPrefix());


}
