#include "../../inc/utils.hpp"







void	mode(Server *server, Client *client) {

	std::string	paramZero = client->getMessage()->getParams()[0];
	std::string	paramUn = client->getMessage()->getParams()[1];

	/* user Mode */
	if (paramZero.size() == 0)
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " MODE : Not enough parameters");
	else if (paramZero[0] == '#') {

		std::cout << "DEBUG ===>  ChannelName: " << paramZero  << std::endl << std::endl;

		std::map<std::string, Channel>::iterator ret = server->getChannels().find(paramZero);
		if (ret == server->getChannels().end())
			std::cout << "DEBUG ===>  No such channel "  << std::endl << std::endl;
		else if (paramZero != client->getChannelName())
			std::cout << "DEBUG ===> You're not channel operator "  << std::endl << std::endl;
		else
			std::cout << "DEBUG ===> Bravo, vous etes operator de ce channel "  << std::endl << std::endl;

	}
	else if (paramZero != client->getNick() && server->nickIsUsed(paramZero) == true) {
		client->sendMsg(ERR_USERSDONTMATCH + client->getNick() + " Can't change mode for other users");
	}
	else if (server->nickIsUsed(paramZero) == false) {
		client->sendMsg(ERR_NOSUCHNICK + client->getNick() + " " + paramZero);
	}
	else if (paramZero == client->getNick() && client->getMessage()->getParams().size() == 1) {
		client->sendMsg(RPL_UMODEIS + client->getNick() + " " + client->getModesString());
	}
	else if (client->getMessage()->getParams().size() > 1) {
		for (size_t i = 1; i < paramUn.size(); i++) {
			if (client->getModes().find(paramUn[i]) == client->getModes().end())
				client->sendMsg(ERR_UMODEUNKNOWNFLAG + client->getNick() + " " + paramUn[i] + " is not implemented, or does not exists");
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

	/* channel Mode  ==> a faire? */

}



/* Command: MODE
  Parameters: <target> [<modestring> [<mode arguments>...]] */

/* USER MODES :
- a : away
- i : invisible
- w : wallops
- r : restricted
- o : operator

CHANNEL MODES :
for users :
    - O : channel creator
    - o : channel operator
    - v : voice
for channels :
    - i : invite only
    - m : moderated
    - n : outside privmsg disabled
    - p : private
    - t : topic locked
    - k : key locked
    - l : user limit */