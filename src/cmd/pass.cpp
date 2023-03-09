#include "../../inc/utils.hpp"

void	pass(Server *server, Client *client)
{
	if (client->getMessage()->getParams().size() == 0 && client->getAuthorized() == false)
	{
		client->setAuthorized(true);
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " PASS :Not enough parameters");
		client->setAuthorized(false);
	}
	else if (client->getMessage()->getParams().size() == 1)
	{
		if (client->getAuthorized() == true)
			client->sendMsg(ERR_ALREADYREGISTERED + client->getNick() + " PASS :Already registered");
		else if (client->getMessage()->getParams()[0] == server->getPassword())
			client->setAuthorized(true);
		else
		{
			client->setAuthorized(true);
			client->sendMsg(ERR_PASSWDMISMATCH + client->getNick() + " PASS :Wrong password");
			client->setAuthorized(false);
			// delete (client);
		}
	}
}

// ERR_NEEDMOREPARAMS
// ERR_ALREADYREGISTRED if getAuthorized == true