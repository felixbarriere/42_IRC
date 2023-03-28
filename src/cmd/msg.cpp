#include "../../inc/utils.hpp"

void	msg(Server* server, Client* client) {
	if (client->getMessage()->getParams().size() == 0 || client->getMessage()->getParams().size() == 1)
		return ;
	if (client->getMessage()->getParams()[0][0] == '#') {
		std::map<std::string, Channel>::iterator	it = server->getChannels().find(client->getMessage()->getParams()[0]);
		if (it != server->getChannels().end()) {
			std::string	params = "";
			for (long unsigned int i = 0; i < client->getMessage()->getParams().size(); i++) {
				params.append(client->getMessage()->getParams()[i]);
				if (i < client->getMessage()->getParams().size())
					params.append(" ");
			}
			it->second.broadcast(client, "MSG " + params);
		}
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
			receiver->sendMsg("MSG " + params, client);
		}
	}
}
