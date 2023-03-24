#include "../../inc/utils.hpp"

void	privmsg(Server* server, Client* client) {
	std::map<std::string, Channel>::iterator	it = server->getChannels().find(client->getMessage()->getParams()[0]);
	if (it != server->getChannels().end()) {
		std::string	params = "";
		for (long unsigned int i = 0; i < client->getMessage()->getParams().size(); i++) {
			params.append(client->getMessage()->getParams()[i]);
			if (i < client->getMessage()->getParams().size())
				params.append(" ");
		}
		it->second.broadcast(client, "PRIVMSG " + params);
	}
}
