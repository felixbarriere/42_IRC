#include "../../inc/utils.hpp"

void	join(Server *server, Client *client, const std::string name) {
	client->setChannel(&(server->getChannels()[name]));
}
