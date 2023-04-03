#include "../../inc/utils.hpp"

void	pass(Server* server, Client* client) {
	if (client->getWelcome()) 
		return ;
	if (client->getMessage()->getParams().size() == 0 && !client->getAuthorized()) {
		client->setAuthorized(true);
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Not enough parameters", client);
		client->setAuthorized(false);
	}
	else if (client->getMessage()->getParams().size() == 1) {
		if (client->getAuthorized())
			client->sendMsg(ERR_ALREADYREGISTERED + client->getNick() + " :You may not reregister", client);
		else if (client->getMessage()->getParams()[0] == server->getPassword())
			client->setAuthorized(true);
		else {
			client->setAuthorized(true);
			client->sendMsg(ERR_PASSWDMISMATCH + client->getNick() + " :Password incorrect", client);
			client->setAuthorized(false);
		}
	}
}
