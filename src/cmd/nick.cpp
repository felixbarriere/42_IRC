#include "../../inc/utils.hpp"

void	nick(Client *client, const std::string nick) {
	client->setNick(nick);
}
