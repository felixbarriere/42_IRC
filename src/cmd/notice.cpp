#include "../../inc/utils.hpp"

void	notice(Server* server, Client* client) {
	if (!server || client->getMessage()->getParams().size() < 2 || \
		!(client->getModes().find('o')->second) || \
		(client->getMessage()->getParams()[0][0] == '#' && !server->getChannelByName(client->getMessage()->getParams()[0])) || \
		(client->getMessage()->getParams()[0][0] != '#' && !server->getClientByNick(client->getMessage()->getParams()[0])))
		return ;
	std::string	params = "";
	for (long unsigned int i = 0; i < client->getMessage()->getParams().size(); i++) {
		params.append(client->getMessage()->getParams()[i]);
		if (i < client->getMessage()->getParams().size())
			params.append(" ");
	}
	if (client->getMessage()->getParams()[0][0] == '#')
		server->getChannelByName(client->getMessage()->getParams()[0])->broadcast(client, "NOTICE " + params);
	else
		server->getClientByNick(client->getMessage()->getParams()[0])->sendMsg("NOTICE " + params, server->getClientByNick(client->getMessage()->getParams()[0]));
}
