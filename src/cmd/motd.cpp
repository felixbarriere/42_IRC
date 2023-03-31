#include "../../inc/utils.hpp"

void	motd(Server* server, Client* client) {
	(void) server;
	if (client->getMessage()->getParams().size()) {
		client->sendMsg(ERR_NOMOTD + client->getNick() + " :Invalid MOTD parameters", client);
		return ;
	}
	std::ifstream	ifs;
	ifs.open("src/motd/motd.txt");
	if (!ifs.good())
		client->sendMsg(ERR_NOMOTD + client->getNick() + " :MOTD file is missing", client);
	else {
		client->sendMsg(RPL_MOTDSTART + (std::string)" : - Message of the day - ", client);
		std::stringstream	s;
		s << ifs.rdbuf();
		client->sendMsg(RPL_MOTD + client->getNick() + " " + s.str(), client);
		client->sendMsg(RPL_ENDOFMOTD + client->getNick() + " :End of /MOTD command", client);
	}
	ifs.close();
}
