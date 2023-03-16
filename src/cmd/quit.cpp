#include "../../inc/utils.hpp"

void	quit(Server* server, Client* client) {
	(void) server;
	// std::cout << "DEBUG ===> QUIT function called from client #" << client->getC_socket()  << std::endl << std::endl;
	// if (client->getChannel() == NULL) {
	// 	std::cout << "DEBUG ===> no channel" << std::endl << std::endl;
	// 	client->sendMsg(" QUIT : Bye for now! " );
	// }
	// client->getChannel() == NULL
	if (client->getMessage()->getParams().size()) {
		std::string	str;
		for (size_t i = 0; i < client->getMessage()->getParams().size(); i++)
			str += client->getMessage()->getParams()[i] + " ";
		// std::cout << "DEBUG ===> QUIT message: " << str << std::endl;
		// std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
		// while (it != server->getChannels().end()) {
		// 	if (&(it->second) == client->getChannel()) {
		// 		std::cout << "//////// TROUVE" << std::endl;
		// 		break ;
		// 	}
		// 	it++;
		// }
		// std::cout << "//////// PAS TROUVE " << std::endl;
		if (client->getChannel())
			client->getChannel()->broadcast(client, client->getNick() + str);
		client->sendMsg("QUIT " + str);
	}
}
