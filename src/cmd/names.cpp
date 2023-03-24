#include "../../inc/utils.hpp"

void	names(Server* server, Client* client) {
	if (!(client->getMessage()->getParams().size())) {
		std::map<int, Client*>::iterator	it = server->getClients().begin();
		while (it != server->getClients().end()) {
			client->sendMsg(it->second->getNick());
			it++;
		}
		return ;
	}
	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (it->first == client->getMessage()->getParams()[0]) {
			std::vector<Client*>::iterator	itt = it->second.getMembers().begin();
			while (itt != it->second.getMembers().end()) {
				client->sendMsg((*itt)->getNick());
				itt++;
			}
			return ;
		}
		it++;
	}
// must send RPL_NAMRPLY_ RFC1459 ( '=' / '*' / '@' ) <channel> ' ' : [ '@' / '+' ] <nick> *( ' ' [ '@' / '+' ] <nick> )
}
