#include "../../inc/utils.hpp"

void	quit(Server* server, Client* client) {
	// std::cout << "DEBUG ===> QUIT function called from client #" << client->getC_socket()  << std::endl << std::endl;
	// if (client->getChannel() == NULL) {
	// 	std::cout << "DEBUG ===> no channel" << std::endl << std::endl;
	// 	client->sendMsg(" QUIT : Bye for now! " );
	// }
	if (client->getMessage()->getParams().size()) {
		std::string	str;
		for (size_t i = 0; i < client->getMessage()->getParams().size(); i++)
			str += client->getMessage()->getParams()[i] + " ";
		std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
		while (it != server->getChannels().end()) {
			if ((it->first) == client->getChannelName()) {
				it->second.broadcast(client, client->getNick() + str);
				client->setChannelName("");
				break ;
			}
			it++;
		}
		client->sendMsg("QUIT " + str);
	}
}
