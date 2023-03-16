#include "../../inc/utils.hpp"

void	mode(Server *server, Client *client) {

	/* user Mode */
	if (client->getMessage()->getParams()[0].size() == 0)
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " MODE : Not enough parameters");
	else if (client->getMessage()->getParams()[0][0] == '#') {

		std::cout << "DEBUG ===>  ChannelName: " << client->getMessage()->getParams()[0]  << std::endl << std::endl;

		std::map<std::string, Channel>::iterator ret = server->getChannels().find(client->getMessage()->getParams()[0]);
		if (ret == server->getChannels().end())
			std::cout << "DEBUG ===>  No such channel "  << std::endl << std::endl;
		else if (client->getMessage()->getParams()[0] != client->getChannelName())
			std::cout << "DEBUG ===> You're not channel operator "  << std::endl << std::endl;
		else
			std::cout << "DEBUG ===> Bravo, vous etes operator de ce channel "  << std::endl << std::endl;

	}
	else if (client->getMessage()->getParams()[0] != client->getNick() && server->nickIsUsed(client->getMessage()->getParams()[0]) == true)
		client->sendMsg(ERR_USERSDONTMATCH + client->getNick() + " Can't change mode for other users");
	else if (server->nickIsUsed(client->getMessage()->getParams()[0]) == false)
		client->sendMsg(ERR_NOSUCHNICK + client->getNick() + " " + client->getMessage()->getParams()[0]);
	else if (client->getMessage()->getParams()[0] == client->getNick() && client->getMessage()->getParams().size() == 1)
		client->sendMsg(RPL_UMODEIS + client->getNick() + " " + client->getModesString());
	else if (client->getMessage()->getParams().size() > 1) {
		for (size_t i = 1; i < client->getMessage()->getParams()[1].size(); i++) {
			if (client->getModes().find(client->getMessage()->getParams()[1][i]) == client->getModes().end())
				client->sendMsg(ERR_UMODEUNKNOWNFLAG + client->getNick() + " " + client->getMessage()->getParams()[1][i] + " is not implemented, or does not exists");
		}
		if (client->getMessage()->getParams()[1][0] == '+') {
			for (size_t i = 1; i < client->getMessage()->getParams()[1].size(); i++)
				client->addMode(client->getMessage()->getParams()[1][i]);
		}
		else if (client->getMessage()->getParams()[1][0] == '-') {
			for (size_t i = 1; i < client->getMessage()->getParams()[1].size(); i++)
				client->removeMode(client->getMessage()->getParams()[1][i]);
		}
	}


}



/* Command: MODE
  Parameters: <target> [<modestring> [<mode arguments>...]] */

