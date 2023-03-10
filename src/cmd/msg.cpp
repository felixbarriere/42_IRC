#include "../../inc/utils.hpp"

void	msg(Server *server, Client *client) {
	(void) server;
	(void) client;
	// std::vector<Client*>::iterator	it = client->getChannel()->getMembers().begin();
	// for (; it != client->getChannel()->getMembers().end() && (*it)->getNick() == client->getMessage()->getParams()[0]; it++)
	// if (it != client->getChannel()->getMembers().end()) {
	// 	for (unsigned long i = 1; i < client->getMessage()->getParams().size(); i++)
	// 		(*it)->sendMsg(client->getMessage()->getParams()[i]);
	// }
	// else {
	// 	std::vector<Client*>::iterator	it = client->getChannel()->getMembers().begin();
	// 	for (; it != client->getChannel()->getMembers().end(); it++) {
	// 		if ((*it) != client) {
	// 			for (unsigned long i = 1; i < client->getMessage()->getParams().size(); i++)
	// 				(*it)->sendMsg(client->getMessage()->getParams()[i]);
	// 		}
	// 	}
	// }
	// std::map<int, Client*>::iterator	it = server->getClients().begin();
	// while (it != server->getClients().end()) {
	// 	if (it->second->getUser() == client->getMessage()->getParams()[0]) {
	// 		for (unsigned long i = 1; i < client->getMessage()->getParams().size(); i++)
	// 			it->second->sendMsg(client->getMessage()->getParams()[i]);
	// 		return ;
	// 	}
	// 	it++;
	// }
}
