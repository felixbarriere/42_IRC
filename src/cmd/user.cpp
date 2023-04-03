#include "../../inc/utils.hpp"

void	user(Server* server, Client* client) {
	(void) server;
	if (client->getUser().size())
		client->sendMsg(ERR_ALREADYREGISTERED + client->getNick() + " :You may not reregister", client);
	else if (client->getMessage()->getParams().size() < 4)
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Not enough parameters", client);
	else if (client->getMessage()->getParams().size() >= 4) {
		client->setUser(client->getMessage()->getParams()[0]);
		std::vector<std::string>::const_iterator it = client->getMessage()->getParams().begin();
		std::vector<std::string>::const_iterator ite = client->getMessage()->getParams().end();
		for (int i = 0; it != ite; it++, i++) {
			if ((*it)[0] == ':')
				client->setRealName((*it).substr(1, ((*it).length() - 1)));
		}
	}
}
