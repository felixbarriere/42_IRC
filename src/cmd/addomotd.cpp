#include "../../inc/utils.hpp"

void	addomotd(Server *server, Client *client) {
	(void) server;
	if (!(client->getModes().find('o')->second))
		return ;
	std::ofstream	out;
	out.open("motd/omotd.txt", std::ios::app);
	out << client->getMessage()->getParams()[0];
}
