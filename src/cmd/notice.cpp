#include "../../inc/utils.hpp"

void	notice(Server* server, Client* client) {
	std::cout << "//////////// DEBUG NOTICE FUNCTION CALLED" << std::endl;
	if (!server || client->getMessage()->getParams().size() < 2 || \
		(client->getMessage()->getParams()[0][0] == '#' && !server->getChannelByName(client->getMessage()->getParams()[0])) || \
		(client->getMessage()->getParams()[0][0] != '#' && !server->getClientByNick(client->getMessage()->getParams()[0])))
		return ;
	std::cout << "//////////// DEBUG NOTICE CHANNEL OR CLIENT FOUND" << std::endl;
}
