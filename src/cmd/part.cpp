#include "../../inc/utils.hpp"

void	part(Server *server, Client *client) {
	if (client->getMessage()->getParams().size() == 0) //si pas de parametres, irssi envoie le nom du channel a partir duquel on PART.
		std::cout << "needs more params!" << std::endl;
	std::cout << "params number: " << client->getMessage()->getParams().size() << std::endl;
	std::cout << "params[0]: " << client->getMessage()->getParams()[0] << std::endl;
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (client->checkChannelName(it->first)) {
			client->sendMsg("PART " + it->first, client);
			it->second.removeMember(client);
			if (it->second.getMembers().size() == 0) {
				server->getChannels().erase(it);
				// std::cout << "Channel deleted" << std::endl << std::endl;
			}
			else
				it->second.broadcast(client, "PART " + it->first);
			break ;
		}
		it++;
	}
}
