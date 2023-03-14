#include "../../inc/utils.hpp"

void	mode(Server *server, Client *client) {
	(void)server;
	(void)client;
	std::cout << "DEBUG ===> MODE function called"  << std::endl << std::endl;


	// user Mode
	if (client->getMessage()->getParams()[0].size() == 0)	// rien d'envoyé par irssi
		std::cout << "DEBUG ===>  no params"  << std::endl << std::endl;
	if (client->getMessage()->getParams()[0][0] == '#')	// rien d'envoyé par irssi
		std::cout << "DEBUG ===>  Channel mode command not supported"  << std::endl << std::endl;
	else if (client->getMessage()->getParams()[0] == client->getNick()) {
		std::cout << "DEBUG ===> good nickname"  << std::endl << std::endl;
	// for ()
	// 	std::cout << "DEBUG ===> " << client->getMo << std::endl << std::endl;

	}
	else
		std::cout << "DEBUG ===>  Cannot change mode for other users"  << std::endl << std::endl;



	// channel Mode  ==> a faire?

}

/* 
		std::map<char, bool>				_modes;
 */ 

/* Command: MODE
  Parameters: <target> [<modestring> [<mode arguments>...]] */

/* USER MODES :
- a : away
- i : invisible
- w : wallops
- r : restricted
- o : operator

CHANNEL MODES :
for users :
    - O : channel creator
    - o : channel operator
    - v : voice
for channels :
    - i : invite only
    - m : moderated
    - n : outside privmsg disabled
    - p : private
    - t : topic locked
    - k : key locked
    - l : user limit */