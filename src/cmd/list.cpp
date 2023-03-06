#include "../../inc/utils.hpp"

void	list(Server *server, Client *client) {
	std::map<std::string, Channel>::const_iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		std::map<char, bool>::const_iterator	m = it->second.getModes().find('s');
		if (!(m->second) || (m->second && client->getModes().find('o')->second))
			std::cout << it->first << std::endl;
		it++;
	}
}
