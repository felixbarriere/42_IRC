#include "../../inc/utils.hpp"

void	privmsg(Server *server, Client *client) {
	std::map<std::string, Channel>::iterator	it = server->getChannels().find(client->getMessage()->getParams()[0]);
	if (it != server->getChannels().end())
		it->second.broadcast(client, "PRIVMSG " + client->getMessage()->getParams()[0] + " " + client->getMessage()->getParams()[1]);
}
