#include "../../inc/utils.hpp"

// https://modern.ircdocs.horse/#nick-message

void	nick(Server* server, Client* client) {
	if (!server)
		return ;
	// && checkCommand(client->getMessage()->getParams()[0]) == true
	if (!client->getWelcome()) {
		if (!checkCommand(client->getMessage()->getParams()[0]) || client->getMessage()->getParams()[0].size() > 9)
			client->sendMsg(ERR_ERRONEUSNICKNAME " :Erroneous nickname", client);
		else if (server->nickIsUsed(client->getMessage()->getParams()[0])) {
			// std::cout << "DEBUG ===> nickname already used"   << std::endl;
			client->sendMsg(ERR_NICKNAMEINUSE + client->getMessage()->getParams()[0] + " " + client->getMessage()->getParams()[0] + " :Nickname is already in use", client);
		}
		else
			client->setNick(client->getMessage()->getParams()[0]);
		return ;
	}
	if (client->getMessage()->getParams().size() == 0)
		client->sendMsg(ERR_NONICKNAMEGIVEN " :No nickname given", client);  // normalement irssi n'envoie rien dans ce cas
	else if (!checkCommand(client->getMessage()->getParams()[0]) || client->getMessage()->getParams()[0].size() > 9)
		client->sendMsg(ERR_ERRONEUSNICKNAME + client->getNick() + " :Erroneous nickname", client);
	else if (server->nickIsUsed(client->getMessage()->getParams()[0]))
		client->sendMsg(ERR_NICKNAMEINUSE + client->getMessage()->getParams()[0] + " " + client->getMessage()->getParams()[0] + " :Nickname is already in use", client);
	else if (client->getAuthorized()) {
		client->sendMsg("NICK " + client->getMessage()->getParams()[0], client);
		client->setNick(client->getMessage()->getParams()[0]);
		// ajouter un broadcast pour avertir les membres du channel concerné d'un nouveau nickname
		if (client->getChannelName().size()) {
			std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
			while (it != server->getChannels().end()) {
				if ((it->first) == client->getChannelName()) {
					it->second.broadcast(client, " changed nickname to " + client->getMessage()->getParams()[0]);
					break ;
				}
				it++;
			}
		}
	}
}
