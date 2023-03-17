#include "../../inc/utils.hpp"

void	part(Server *server, Client *client) {
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (it->first == client->getChannelName()) {
			it->second.removeMember(client);
			client->sendMsg("PART " + it->first);
			it->second.broadcast(client, "PART " + it->first);
			if (client->getNick() == it->second.getCreator()->getNick() || it->second.getMembers().size() == 0)
			{
				server->getChannels().erase(it);
				std::cout << "Channel deleted" << std::endl << std::endl;
			}

			break ;
		}
		it++;
	}
}
