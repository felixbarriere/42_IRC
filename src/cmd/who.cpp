#include "../../inc/utils.hpp"


/* Visible users are users who aren’t invisible (user mode +i) and who don’t have a 
common channel with the requesting client. */


bool	commonChannel(Client* client1, Client* client2)	{
	std::vector<std::string>::iterator	it = client1->getChannelsNames().begin();
	std::vector<std::string>::iterator	ite = client1->getChannelsNames().end();
	for (; it != ite; it++) {
		std::vector<std::string>::iterator	it2 = client2->getChannelsNames().begin();
		std::vector<std::string>::iterator	ite2 = client2->getChannelsNames().end();
		for (; it2 != ite2; it++) {
			if (it == it2) {
				std::cout << "debug =====> commonChan: " << (*it) << std::endl;
				return true;
			}
		}
	}
	std::cout << "debug =====> no commonChan" << std::endl;

	return (false);
}


void	who(Server* server, Client* client) {
	(void) server;
	(void) client;

	std::cout << std::endl << "Function WHO" << std::endl << std::endl;

	if (client->getMessage()->getParams()[0].size() == 0) {		/* no arg */
		std::cout << "debug =====>no param: list user with nc" << std::endl;
		
		std::map<int, Client*>::iterator	it = server->getClients().begin();	
		std::map<int, Client*>::iterator	ite = server->getClients().end();
		for (; it != ite; it++) {
			if (it->second->getModes().find('i')->second == false && commonChannel(it->second, client) == false) 
				client->sendMsg(RPL_WHOREPLY + it->second->getNick() + " User: " + it->second->getUser() + " " + it->second->getHostname() + " IRC " + it->second->getNick() + " H" , client);
		}
		client->sendMsg(RPL_ENDOFWHO " :End of WHO list", client);
	}
	else if (client->getMessage()->getParams()[0][0] != '#') {		/* arg == user */
		std::cout << "debug =====>param: user: " << client->getMessage()->getParams()[0] << std::endl;

		std::map<int, Client*>::iterator	it = server->getClients().begin();
		std::map<int, Client*>::iterator	ite = server->getClients().end();
		for (; it != ite; it++) {
			if (it->second->getNick() == client->getMessage()->getParams()[0]) {
				if (it->second->getModes().find('i')->second == false && commonChannel(it->second, client) == false) 
					client->sendMsg(RPL_WHOREPLY + it->second->getNick() + " User: " + it->second->getUser() + " " + it->second->getHostname() + " IRC " + it->second->getNick() + " H" , client);
				client->sendMsg(RPL_ENDOFWHO " :End of WHO list", client);
				return ;
				}
			}
        client->sendMsg(ERR_NOSUCHNICK + client->getNick() + " " + client->getMessage()->getParams()[0] + " :No such nickname", client);
	}
	else {	/*  arg == channel */
		if (server->getChannels().count(client->getMessage()->getParams()[0]) == 0) {  
	        client->sendMsg(ERR_NOSUCHCHANNEL + client->getNick() + " " + client->getMessage()->getParams()[0] + " :No such channel", client);
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
	}

// must send RPL_WHOISUSER, RPL_WHOISSERVER, RPL_WHOISOPERATOR, RPL_WHOISIDLE, RPL_ENDOFWHOIS, RPL_WHOISCHANNELS, RPL_WHOISSECURE, RPL_WHOISLANGUAGE
}
