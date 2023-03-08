#include "../../inc/utils.hpp"

void	wallops(Server *server, Client *client) {
	if (!(client->getModes().find('o')->second))
		return ;
	std::map<int, Client*>::iterator	it = server->getClients().begin();
	while (it != server->getClients().end()) {
		if (it->second->getModes().find('w')->second) {
			for (unsigned long i = 0; i < client->getMessage()->getParams().size(); i++)
				it->second->sendMsg(client->getMessage()->getParams()[i]);
		}
		it++;
	}
}

