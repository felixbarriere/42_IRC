#include "../../inc/utils.hpp"


/* Visible users are users who aren’t invisible (user mode +i) and who don’t have a 
common channel with the requesting client. */


void	who(Server* server, Client* client) {
	(void) server;
	(void) client;

	std::cout << std::endl << "Function WHO" << std::endl << std::endl;

	if (server->getChannels().count(client->getMessage()->getParams()[0]) == 0) {  // attention, on peut aussi avoir un nickname en arg
        client->sendMsg(ERR_NOSUCHCHANNEL + client->getNick() + " " + client->getMessage()->getParams()[0] + " :No such channel or nickname", client);
		return ;
	}

	std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
	while (it != server->getChannels().end()) {
		if (it->first == client->getMessage()->getParams()[0]) {  

			std::cout << "debug =====>param: this channel exists" << std::endl;
			
			// checker si client est egalement dans le channel. S'il n'y est pas, on prend 'i' en compte	

			std::string	str;
			std::vector<Client*>::iterator	itt = it->second.getMembers().begin();
			while (itt != it->second.getMembers().end()) {
				if ((*itt)->getModes().find('i')->second == false && client->checkChannelName(it->first) == false) {

					// str += (*itt)->getNick() + " ";
					client->sendMsg(RPL_WHOREPLY + (*itt)->getNick() + " " + it->first + " " + (*itt)->getUser() + " " + (*itt)->getHostname() + " IRC " + (*itt)->getNick() + " H" , client);
					// RPL_WHOREPLY "<channel> <user> <host> <server> <nick>
				}
				itt++;
			}
			std::string chan = it->first;
			std::cout << "channel name is " << chan << std::endl;
			std::string msg = RPL_ENDOFWHO + chan + " :End of WHO list";
			// client->sendMsg(RPL_WHOREPLY + str , client);
			client->sendMsg(msg, client);
			return ;
		}
		it++;
	}

// must send RPL_WHOISUSER, RPL_WHOISSERVER, RPL_WHOISOPERATOR, RPL_WHOISIDLE, RPL_ENDOFWHOIS, RPL_WHOISCHANNELS, RPL_WHOISSECURE, RPL_WHOISLANGUAGE
}
