#include "../../inc/utils.hpp"

void	addmotd(Server *server, Client *client) {
	(void) server;
	if (!(client->getModes().find('o')->second))
		return ;
	std::ofstream	out;
	out.open("motd/motd.txt", std::ios::app);
	out << client->getMessage()->getParams()[0];
}
