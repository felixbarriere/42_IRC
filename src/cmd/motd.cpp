#include "../../inc/utils.hpp"

void	motd(Server* server, Client* client) {
	(void) server;
	if (!(client->getModes().find('o')->second))
		return ;
	std::ifstream	ifs;
	ifs.open("src/motd/motd.txt");
	std::stringstream	s;
	s << ifs.rdbuf();
	client->sendMsg(s.str());
// must send RPL_MOTD RFC1459 :- <string>
}
