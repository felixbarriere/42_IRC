#include "../../inc/utils.hpp"

void	addmotd(Client *client, const std::string text) {
	if (!(client->getOper()))
		return ;
	std::ofstream	out;
	out.open("motd/motd.txt", std::ios::app);
	out << text;
}
