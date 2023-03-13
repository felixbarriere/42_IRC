#include "../../inc/utils.hpp"

void	mode(Server *server, Client *client) {
	(void)server;
	(void)client;

	// user Mode

	// channel Mode

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