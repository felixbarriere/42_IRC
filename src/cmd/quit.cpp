#include "../../inc/utils.hpp"

void	quit(Server* server, Client* client) {
	// if (client->getMessage()->getParams().size()) {
		std::string	str;
		for (size_t i = 0; i < client->getMessage()->getParams().size(); i++)
			str += client->getMessage()->getParams()[i] + " ";
		std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
		while (it != server->getChannels().end()) {
			if (client->checkChannelName(it->first)) {		//Client is part of an existing Channel
				// std::cout << "Client is part of an existing Channel" << std::endl;
				it->second.broadcast(client, client->getNick() + str);
				// client->setChannelName("");
				client->removeChannelName(it->first);
				it->second.removeMember(client);  // a bien tester
				std::cout << "Creator:" << it->second.getCreator()->getNick() << std::endl;
				std::cout << "Client Nick:" << client->getNick() << std::endl;
				if (it->second.getCreator()->getNick() == client->getNick() || it->second.getMembers().size() == 0) {
					// std::cout << "Client is creator of this channel" << std::endl;
					server->getChannels().erase(it);
				}
				break ;
			}
			it++;
		}
		client->sendMsg("QUIT " + str, client);
		client->setNick("");
		// server->getClients().erase(client->getC_socket());
		// delete (client);
	// }
}
