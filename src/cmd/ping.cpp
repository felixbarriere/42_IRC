#include "../../inc/utils.hpp"

void	ping(Server* server, Client* client) {
	(void) server;
	(void) client;
	if (!client->getWelcome())
		return ;
	if (client->getMessage()->getParams()[0].size() <= 0) 
		client->sendMsg(ERR_NOORIGIN + client->getNick() + ":No origin specified");
	else
		client->sendMsg("PONG " + client->getNick() + " :" + client->getMessage()->getParams()[0]);
}
