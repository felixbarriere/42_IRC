#include "../../inc/utils.hpp"

void	join(Server *server, Client *client) {
	client->getChannel()->removeMember(client);
	client->setChannel(&(server->getChannels()[client->getMessage()->getParams()[0]]));
	client->getChannel()->addMember(client);
}
