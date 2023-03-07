#include "../../inc/utils.hpp"

void	join(Server *server, Client *client) {
	(void) server;
	if (!client->getMessage()->getParams().size())
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + ": err need more params");
	// std::map<std::string, Channel>::iterator	it = server->getChannels().find(client->getMessage()->getParams()[0]);
	// if (it == server->getChannels().end()) {
	// 	if (client->getChannel())
	// 		client->getChannel()->removeMember(client);
	// 	client->setChannel(&(server->getChannels()[client->getMessage()->getParams()[0]]));
	// 	client->getChannel()->addMember(client);
	// 	client->getChannel()->setCreator(client);
	// }
	// else {

	// }
}
