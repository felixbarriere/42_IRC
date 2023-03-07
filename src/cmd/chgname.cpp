#include "../../inc/utils.hpp"

void	chgname(Server *server, Client *client) {
	if (!(client->getModes().find('o')->second))
		return ;
	std::map<int, Client*>::iterator	it = server->getClients().begin();
	while (it != server->getClients().end()) {
		if (it->second->getUser() == client->getMessage()->getParams()[1]) {
			it->second->setUser(client->getMessage()->getParams()[0]);
			return ;
		}
		it++;
	}
}
