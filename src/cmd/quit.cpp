#include "../../inc/utils.hpp"

void	quit(Server* server, Client* client) {
	if (client->getMessage()->getParams().size()) {
		std::string	str;
		for (size_t i = 0; i < client->getMessage()->getParams().size(); i++)
			str += client->getMessage()->getParams()[i] + " ";
		std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
		while (it != server->getChannels().end()) {
			if ((it->first) == client->getChannelName()) {
				it->second.broadcast(client, client->getNick() + str);
				client->setChannelName("");
				break ;
			}
			it++;
		}
		client->sendMsg("QUIT " + str);
		client->setNick("");
		// server->getClients().erase(client->getC_socket());
		// delete (client);
	}
}
