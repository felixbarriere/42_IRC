#include "../../inc/utils.hpp"

void	quit(Server* server, Client* client) {
	std::string	str;
	for (size_t i = 0; i < client->getMessage()->getParams().size(); i++) {
		if (client->getMessage()->getParams()[i].size() != 1)
			str += client->getMessage()->getParams()[i] + " ";
	}
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (client->checkChannelName(it->first)) {
			client->getMessage()->getParams().clear();
			client->getMessage()->getParams().push_back(it->first);
			part(server, client);
			it->second.broadcast(client, "QUIT " + str);
			client->removeChannelName(it->first);
			it->second.removeMember(client);
			if (it->second.getMembers().size() == 0)
				server->getChannels().erase(it++);
			else
				it++;
		}
		else
			it++;
	}
	client->sendMsg("QUIT " + str + " :Client quit", client);
	client->setConnected(false);
}
