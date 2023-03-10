#include "../../inc/utils.hpp"

void	join(Server *server, Client *client) {
	if (client->getMessage()->getParams().size() == 0)
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + ": err need more params");
	else {
		std::string	channel_name = client->getMessage()->getParams()[0];
		if (channel_name[0] != '#')
			channel_name = "#" + channel_name;
		std::map<std::string, Channel>::iterator	it = server->getChannels().find(channel_name);
		if (it == server->getChannels().end()) {
			Channel	channel(client);
			server->getChannels().insert(std::make_pair(channel_name, channel));
			client->setChannel(&channel);
		}
		else {
			it->second.addMember(client);
			client->setChannel(&(it->second));
			it->second.broadcast(client, "JOIN " + it->first);
		}
		client->sendMsg("JOIN " + channel_name);
	}
}

// lancer NAMES
// check pwd
// check limit
