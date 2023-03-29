#include "../../inc/utils.hpp"

void	names(Server* server, Client* client) {

	std::cout << "debug =====> fonction names" << std::endl;


	if (!(client->getMessage()->getParams().size())) {
		std::map<int, Client*>::iterator	it = server->getClients().begin();
		while (it != server->getClients().end()) {
			client->sendMsg(it->second->getNick(), client);
			it++;
		}
		return ;
	}
	std::cout << "debug =====> test" << std::endl;

	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (it->first == client->getMessage()->getParams()[0]) {
			std::string	str;
			std::vector<Client*>::iterator	itt = it->second.getMembers().begin();
			while (itt != it->second.getMembers().end()) {
				if ((*itt)->getModes().find('i')->second == false) {
					str += (*itt)->getNick() + " ";
				}
				itt++;
			}
			client->sendMsg(RPL_NAMREPLY + str , client);
			client->sendMsg(RPL_ENDOFNAMES " End of NAMES list" , client);
			return ;
		}
		it++;
	}
// must send RPL_NAMRPLY_ RFC1459 ( '=' / '*' / '@' ) <channel> ' ' : [ '@' / '+' ] <nick> *( ' ' [ '@' / '+' ] <nick> )
}
