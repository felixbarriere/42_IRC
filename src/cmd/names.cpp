#include "../../inc/utils.hpp"

void	names(Server* server, Client* client) {
	if (!(client->getMessage()->getParams().size())) {
		std::map<int, Client*>::iterator	it = server->getClients().begin();
		while (it != server->getClients().end()) {
			client->sendMsg(it->second->getNick(), client);
			it++;
		}
		return ;
	}
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (it->first == client->getMessage()->getParams()[0]) {  //ajouter if (client est membre du channel)
			std::string	str;
			std::vector<Client*>::iterator	itt = it->second.getMembers().begin();
			while (itt != it->second.getMembers().end()) {
				if ((*itt)->getModes().find('i')->second == false)
					str += "=" + (*itt)->getNick() + " ";
				itt++;
			}
			client->sendMsg(RPL_NAMREPLY + str , client);
			if (itt != it->second.getMembers().end())
				client->sendMsg(RPL_ENDOFNAMES + (*itt)->getNick() + it->first + " :End of NAMES list", client);
			return ;
		}
		it++;
	}
}
