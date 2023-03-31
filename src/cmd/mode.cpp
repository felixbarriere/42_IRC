#include "../../inc/utils.hpp"

void	mode(Server* server, Client* client) {
	std::string	paramZero = client->getMessage()->getParams()[0];
	std::string	paramUn = client->getMessage()->getParams()[1];
	// user Mode
	if (paramZero.size() == 0)
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Not enough parameters", client);
	else if (paramZero[0] == '#') {
		// std::cout << "DEBUG ===>  ChannelName: " << paramZero  << std::endl << std::endl;
		std::map<std::string, Channel>::iterator ret = server->getChannels().find(paramZero);
		if (ret == server->getChannels().end())
			client->sendMsg("No such channel", client);
		else
			client->sendMsg("Sorry, MODE command is not implemented for channels.", client);
	}	// channel Mode
	else if (paramZero != client->getNick() && server->nickIsUsed(paramZero))
		client->sendMsg(ERR_USERSDONTMATCH + client->getNick() + " Can't change mode for other users", client);
	else if (!server->nickIsUsed(paramZero))
		client->sendMsg(ERR_NOSUCHNICK + client->getNick() + " " + paramZero, client);
	else if (paramZero == client->getNick() && client->getMessage()->getParams().size() == 1)
		client->sendMsg(RPL_UMODEIS + client->getNick() + " " + client->getModesString(), client);
	else if (client->getMessage()->getParams().size() > 1) {
		if (paramUn[0] == '+' || paramUn[0] == '-') {
			for (size_t i = 1; i < paramUn.size(); i++) {
				if (paramUn[i] == 'o') {
					client->sendMsg(client->getNick() + " " + paramUn[i] + " :please use OPER command", client);
					return ;
				}
				else if (client->getModes().find(paramUn[i]) == client->getModes().end())
					client->sendMsg(ERR_UMODEUNKNOWNFLAG + client->getNick() + " " + paramUn[i] + " is not implemented, or does not exists", client);
			}
			if (paramUn[0] == '+') {
				for (size_t i = 1; i < paramUn.size(); i++)
					client->addMode(paramUn[i]);
			}
			else if (paramUn[0] == '-') {
				for (size_t i = 1; i < paramUn.size(); i++)
					client->removeMode(paramUn[i]);
			}
		}
		else 
			client->sendMsg(ERR_UMODEUNKNOWNFLAG + client->getNick() + " modestring should start with '-' or '+'", client);
	}
}

/* Command: MODE
  Parameters: <target> [<modestring> [<mode arguments>...]] */
