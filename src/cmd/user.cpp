#include "../../inc/utils.hpp"

void	user(Server *server, Client *client) {
	(void) server;
	client->setUser(client->getMessage()->getParams()[0]);
}
