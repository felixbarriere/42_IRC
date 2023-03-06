#include "../../inc/utils.hpp"

void	nick(Server *server, Client *client) {
	(void) server;
	client->setNick(client->getMessage()->getParams()[0]);
}
