#include "../../inc/utils.hpp"







void	mode(Server *server, Client *client) {
	std::cout << "DEBUG ===> MODE function called"  << std::endl << std::endl;

	/* user Mode */
	if (client->getMessage()->getParams()[0].size() == 0) {
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " MODE : Not enough parameters");
	}	// rien d'envoyé par irssi
	else if (client->getMessage()->getParams()[0][0] == '#') {
		std::cout << "DEBUG ===>  Channel mode command not supported"  << std::endl << std::endl;
	}
	else if (client->getMessage()->getParams()[0] != client->getNick() && server->nickIsUsed(client->getMessage()->getParams()[0]) == true) {
		client->sendMsg(ERR_USERSDONTMATCH + client->getNick() + " Can't change mode for other users");
	}
	else if (server->nickIsUsed(client->getMessage()->getParams()[0]) == false) {
		client->sendMsg(ERR_NOSUCHNICK + client->getNick() + " " + client->getMessage()->getParams()[0]);
	}
	else if (client->getMessage()->getParams()[0] == client->getNick() && client->getMessage()->getParams().size() == 1) {
		client->sendMsg(RPL_UMODEIS + client->getNick() + " " + client->getModesString());
	}
	else if (client->getMessage()->getParams().size() > 1) //modestring exists
	{
		for (size_t i = 1; i < client->getMessage()->getParams()[1].size(); i++) {
			if (client->getModes().find(client->getMessage()->getParams()[1][i]) == client->getModes().end())
			{
				std::cout << "DEBUG ===> HOLA"  << std::endl << std::endl;
				client->sendMsg(ERR_UMODEUNKNOWNFLAG + client->getNick() + " " + client->getMessage()->getParams()[1][i] + " is not implemented, or does not exists");
			}
		}
		if (client->getMessage()->getParams()[1][0] == '+')
		{
			for (size_t i = 1; i < client->getMessage()->getParams()[1].size(); i++) {
				client->addMode(client->getMessage()->getParams()[1][i]);
			}
		}
		else if (client->getMessage()->getParams()[1][0] == '-')
		{
			for (size_t i = 1; i < client->getMessage()->getParams()[1].size(); i++) {
				client->removeMode(client->getMessage()->getParams()[1][i]);
			}
		}
		//  if not implemented: ERR_UMODEUNKNOWNFLAG
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