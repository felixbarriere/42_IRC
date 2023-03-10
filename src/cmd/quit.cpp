#include "../../inc/utils.hpp"

void	quit(Server *server, Client *client) {
	(void) server;
	(void) client;
	std::cout << "DEBUG ===> QUIT function called from client #" << client->getC_socket()  << std::endl << std::endl;

	// if (client->getChannel() == NULL) {
	// 	std::cout << "DEBUG ===> no channel" << std::endl << std::endl;
	// 	client->sendMsg(" QUIT : Bye for now! " );
	// }
if (client->getMessage()->getParams().size() > 0)	// client->getChannel() == NULL
	{
		std::cout << "DEBUG ===> message: ";
		std::string	str;

		// std::vector<std::string>::iterator	it = getParams().begin();
		// std::vector<std::string>::iterator	ite = getParams().end();
		for (size_t i = 0; i < client->getMessage()->getParams().size(); i++)
		{
			// std::cout << client->getMessage()->getParams()[i] << std::endl;
			str+= client->getMessage()->getParams()[i];
		}
		std::cout << str << std::endl;

	}

}