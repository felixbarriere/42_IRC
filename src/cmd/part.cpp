#include "../../inc/utils.hpp"

void	part(Server *server, Client *client) {
	Channel	*c = client->getChannel();
	if (!c)
		return ;
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end() && &(it->second) != c) {
			client->sendMsg("PART " + it->first);
			it->second.broadcast(client, "PART " + it->first);
			it++;
	}
}
