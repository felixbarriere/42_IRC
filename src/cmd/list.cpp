#include "../../inc/utils.hpp"

void	list(Server* server, Client* client) {
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		std::map<char, bool>::iterator	m = it->second.getModes().find('s');
		if ((!(m->second) || (m->second && client->getModes().find('o')->second)) && it->second.getMembers().size())
			client->sendMsg(RPL_LIST + client->getNick() + " " + it->first, client);
		it++;
	}
	client->sendMsg(RPL_LISTEND + (std::string)" :End of /LIST", client);
}
