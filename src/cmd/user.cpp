#include "../../inc/utils.hpp"

void	user(Server* server, Client* client) {
	(void) server;
	// std::cout << "DEBUG ===> USER function called"  << std::endl << std::endl;
	if (client->getUser().size()) { // || client->getWelcome() == true
		// std::cout << "DEBUG ===> test"  << std::endl << std::endl;
		client->sendMsg(ERR_ALREADYREGISTERED + client->getNick() + " :You may not reregister", client);
	}
	else if (client->getMessage()->getParams().size() < 4)
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Not enough parameters", client);
	else if (client->getMessage()->getParams().size() >= 4) {
		client->setUser(client->getMessage()->getParams()[0]);
		std::vector<std::string>::const_iterator it = client->getMessage()->getParams().begin();
		std::vector<std::string>::const_iterator ite = client->getMessage()->getParams().end();
		for (int i = 0; it != ite; it++, i++) {
			// std::cout << "ET ENCORE ICI2:" << (*it)[0]  << std::endl;
			if ((*it)[0] == ':')
				client->setRealName((*it).substr(1, ((*it).length() - 1)));
		}
	}
}

// must send RPL_NOUSERS RFC1459 :<info>    ==> pas vu dans la doc

// ERR_NEEDMOREPARAMS : "<client> <command> :Not enough parameters"
// It must be noted that <realname> must be the last parameter because it may contain SPACE (' ', 0x20) characters, and should be prefixed with a colon (:) if required.
