#include "../../inc/utils.hpp"

void	privmsg(Server* server, Client* client) {
	if (client->getMessage()->getParams().size() == 0)
		client->sendMsg(ERR_NORECIPIENT + client->getNick() + " :No recipient given", client);
	else if (client->getMessage()->getParams().size() == 1)
		client->sendMsg(ERR_NOTEXTTOSEND + client->getNick() + " :No text to send", client);
	else if (client->getMessage()->getParams()[0][0] == '#' || client->getMessage()->getParams()[0][0] == '!'
	|| client->getMessage()->getParams()[0][0] == '&' || client->getMessage()->getParams()[0][0] == '+') 
	{
		std::map<std::string, Channel>::iterator	it = server->getChannels().find(client->getMessage()->getParams()[0]);
		if (it != server->getChannels().end()) {
			std::string	params = "";
			for (long unsigned int i = 0; i < client->getMessage()->getParams().size(); i++) {
				params.append(client->getMessage()->getParams()[i]);
				if (i < client->getMessage()->getParams().size())
					params.append(" ");
			}
			it->second.broadcast(client, "PRIVMSG " + params);
		}
		else
			client->sendMsg(ERR_NOSUCHCHANNEL + (std::string)" :No such channel.", client);
	}
	else {
		Client*	receiver = server->getClientByNick(client->getMessage()->getParams()[0]);
		if (receiver) {
			std::string	params = "";
			for (long unsigned int i = 0; i < client->getMessage()->getParams().size(); i++) {
				params.append(client->getMessage()->getParams()[i]);
				if (i < client->getMessage()->getParams().size())
					params.append(" ");
			}
			receiver->sendMsg("PRIVMSG " + params, client);
		}
		else
			client->sendMsg(ERR_NOSUCHNICK + (std::string)" :No such nick", client);
	}
}
