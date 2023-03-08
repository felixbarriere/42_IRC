#include "../../inc/utils.hpp"

void	ping(Server *server, Client *client) {
	(void)server;
	(void)client;
	if (client->getWelcome() == false)
		return ;

	if (client->getMessage()->getParams()[0].size() <= 0)
		client->sendMsg("409 " + client->getNick() +":No origin specified");

	client->sendMsg("PONG " + client->getMessage()->getParams()[0]);


}
