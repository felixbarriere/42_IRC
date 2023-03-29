#include "../../inc/utils.hpp"

void	wallops(Server* server, Client* client) {
	if (!server)
		return ;

	std::string msg;
	for (unsigned long i = 0; i < client->getMessage()->getParams().size(); i++)
		msg += " " + client->getMessage()->getParams()[i];
	std::cout << "message is : " << msg << std::endl;
	std::cout << "DEBUG ===> WALLOPS called"  << std::endl << std::endl;

	if(client->getMessage()->getParams().size() < 1) {
        client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + ":Not enough parameters", client);}

	if(!(client->getModes().find('o')->second)) {
		client->sendMsg(ERR_NOPRIVILEGES + client->getNick() +  " :Permission Denied - You're not an IRC operator", client);
	}
	else if(!(client->getModes().find('w')->second)) {
		client->sendMsg(client->getNick() +  " :Permission Denied - You're not +w", client);
	}
	else {
		msg = client->getPrefix() + " WALLOPS " + msg;
		std::cout << "the whole message is : " << msg << std::endl;
		std::map<int, Client*>::iterator	it = server->getClients().begin();
		while (it != server->getClients().end()) {
			if (it->second->getModes().find('w')->second && it->second->getModes().find('o')->second) 
					it->second->sendMsg(msg, client);
			else
				client->sendMsg(client->getNick() +  " :Permission Denied - receiver is not +o or +w", client);
			it++;
		}
	}
}
