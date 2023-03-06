#include "../../inc/utils.hpp"

void	msg(Server *server, Client *client) {
	std::map<int, Client*>::const_iterator	it = server->getClients().begin();
	while (it != server->getClients().end()) {
		if (it->second->getUser() == client->getMessage()->getParams()[0]) {
// evidemment ici cout chez l'autre client
			for (unsigned long i = 1; i < client->getMessage()->getParams().size(); i++)
				std::cout << client->getMessage()->getParams()[i] << std::endl;
			return ;
		}
		it++;
	}
}
