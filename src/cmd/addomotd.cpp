#include "../../inc/utils.hpp"

void	addomotd(Client *client, const std::string text) {
	if (!(client->getOper()))
		return ;
	std::ofstream	out;
	out.open("motd/omotd.txt", std::ios::app);
	out << text;
}
