#include "../../inc/utils.hpp"

void	names(Server *server, Client *client) {
	(void) server;
	std::vector<Client*>::const_iterator	it = client->getChannel()->getMembers().begin();
	while (it != client->getChannel()->getMembers().end()) {
		std::cout << (*it)->getNick() << std::endl;
		it++;
	}
}
