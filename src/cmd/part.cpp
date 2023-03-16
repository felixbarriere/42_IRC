#include "../../inc/utils.hpp"

void	part(Server *server, Client *client) {
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (it->first == client->getChannelName()) {
			client->sendMsg("PART " + it->first);
			it->second.broadcast(client, "PART " + it->first);
			break ;
		}
		it++;
	}
}
