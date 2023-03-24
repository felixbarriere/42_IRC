#include "../../inc/utils.hpp"

void	part(Server *server, Client *client) {
	if (client->getMessage()->getParams().size() == 0) //si pas de parametres, irssi envoie le nom du channel a partir duquel on PART.
		std::cout << "needs more params!" << std::endl;
	std::cout << "params number: " << client->getMessage()->getParams().size() << std::endl;
	std::cout << "params[0]: " << client->getMessage()->getParams()[0] << std::endl;
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		// std::cout << "test" << std::endl;
		if (client->checkChannelName(it->first)) {
			// std::cout << "test2" << std::endl;
			client->sendMsg("PART " + it->first);
			it->second.removeMember(client);
			if (client->getNick() == it->second.getCreator()->getNick() || it->second.getMembers().size() == 0) {
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
