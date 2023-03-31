#include "../../inc/utils.hpp"

void	quit(Server* server, Client* client) {
	std::string	str;

	for (size_t i = 0; i < client->getMessage()->getParams().size(); i++)
		str += client->getMessage()->getParams()[i] + " ";

	std::cout << "CMD quit: params: " << str << std::endl;
	
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (client->checkChannelName(it->first)) {		//Client is part of an existing Channel
		
			std::cout << "Client is part of an existing Channel" << std::endl;

			client->getMessage()->getParams().clear();
			client->getMessage()->getParams().push_back(it->first);

			part(server, client);

			it->second.broadcast(client, "QUIT " + str);

			client->removeChannelName(it->first);
			it->second.removeMember(client);  // a bien tester

			if (it->second.getMembers().size() == 0) {
				server->getChannels().erase(it++);
			}
			else
				it++;
		}
		else
			it++;
	}
	client->sendMsg("QUIT " + str, client);
	client->setConnected(false);
}
