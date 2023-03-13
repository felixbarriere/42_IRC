#include "../../inc/utils.hpp"

void	pass(Server *server, Client *client)
{
		std::cout << "DEBUG ===> PASS  " << std::endl;

	if (client->getMessage()->getParams().size() == 0 && client->getAuthorized() == false)
	{
		std::cout << "DEBUG ===> PASS 1 " << std::endl;

		client->setAuthorized(true);
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " PASS : Not enough parameters");
		client->setAuthorized(false);
	}
	else if (client->getMessage()->getParams().size() == 1)
	{
		std::cout << "DEBUG ===> PASS 2 " << std::endl;

		if (client->getAuthorized() == true)
			client->sendMsg(ERR_ALREADYREGISTERED + client->getNick() + " PASS : Already registered");
		else if (client->getMessage()->getParams()[0] == server->getPassword())
			client->setAuthorized(true);
		else
		{
		std::cout << "DEBUG ===> PASS 3 " << std::endl;
			client->setAuthorized(true);
			client->sendMsg(ERR_PASSWDMISMATCH + client->getNick() + " PASS : Wrong password");
			client->setAuthorized(false);
			// delete (client);
		}
	}
}

// ERR_NEEDMOREPARAMS
// ERR_ALREADYREGISTRED if getAuthorized == true