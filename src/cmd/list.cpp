#include "../../inc/utils.hpp"

void	list(Client *client, const Server *server) {
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		std::map<char, bool>::iterator	m = it->second.getModes().find('s');
		if (!(m->second) || (m->second && client->getOper()))
			std::cout << it->first << std::endl;
		it++;
	}
}
