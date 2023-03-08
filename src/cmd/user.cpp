#include "../../inc/utils.hpp"

void	user(Server *server, Client *client) {
	(void) server;
	std::cout << "DEBUG ===> USER function called"  << std::endl << std::endl;

	if (client->getUser().size() != 0 ) // || client->getWelcome() == true
		client->sendMsg(ERR_ALREADYREGISTERED + client->getNick() + " USER : already registered");
	else if (client->getMessage()->getParams().size() < 4)
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " USER :Not enough parameters");
	else if (client->getMessage()->getParams().size() >= 4)
	{
		client->setUser(client->getMessage()->getParams()[0]);
		
		std::vector<std::string>::const_iterator it = client->getMessage()->getParams().begin();
		std::vector<std::string>::const_iterator ite = client->getMessage()->getParams().end();
		for (int i = 0; it != ite; it++, i++)
		{
			std::cout << "ET ENCORE ICI:" << *it  << std::endl;
			std::cout << "ET ENCORE ICI2:" << (*it)[0]  << std::endl;
			if ((*it)[0] == ':')
				client->setRealName((*it).substr(1, ((*it).length() - 1)));
		}
		std::cout << "DEBUG ===> real_name: "  << client->getRealName() << std::endl;
	}
}


// must send RPL_NOUSERS RFC1459 :<info>    ==> pas vu dans la doc

// ERR_NEEDMOREPARAMS : "<client> <command> :Not enough parameters"
// It must be noted that <realname> must be the last parameter because it may contain SPACE (' ', 0x20) characters, and should be prefixed with a colon (:) if required.