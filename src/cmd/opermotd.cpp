#include "../../inc/utils.hpp"

void	opermotd(Server *server, Client *client) {
	(void) server;
	if (!(client->getModes().find('o')->second))
		return ;
	std::ifstream	ifs;
	ifs.open("src/motd/omotd.txt");
	std::stringstream	s;
	s << ifs.rdbuf();
	client->sendMsg(s.str());
}
