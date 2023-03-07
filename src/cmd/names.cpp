#include "../../inc/utils.hpp"

void	names(Server *server, Client *client) {
	if (!(client->getMessage()->getParams().size())) {
		std::map<int, Client*>::iterator	it = server->getClients().begin();
		while (it != server->getClients().end()) {
			std::cout << it->second->getNick() << std::endl;
			it++;
		}
		return ;
	}
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (it->first == client->getMessage()->getParams()[0]) {
			std::vector<Client*>::iterator	itt = it->second.getMembers().begin();
			while (itt != it->second.getMembers().end()) {
				std::cout << (*itt)->getNick() << std::endl;
				itt++;
			}
			return ;
		}
		it++;
	}
}
