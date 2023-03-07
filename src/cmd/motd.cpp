#include "../../inc/utils.hpp"

void	motd(Server *server, Client *client) {
	(void) server;
	if (!(client->getModes().find('o')->second))
		return ;
	std::fstream	fp;
	char			ch;
	fp.open("motd/motd.txt", std::fstream::in);
	while (fp >> std::noskipws >> ch)
		std::cout << ch;
	fp.close();
	std::cout << std::endl;
// must send RPL_MOTD RFC1459 :- <string>
}
