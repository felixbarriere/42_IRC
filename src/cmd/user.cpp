#include "../../inc/utils.hpp"

void	user(Client *client, const std::string user) {
	client->setUser(user);
}
