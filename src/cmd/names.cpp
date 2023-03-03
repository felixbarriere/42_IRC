#include "../../inc/utils.hpp"

void	names(Channel *channel) {
	std::vector<Client*>::iterator	it = channel->getMembers().begin();
	while (it != channel->getMembers().end()) {
		std::cout << (*it)->getNick() << std::endl;
		it++;
	}
}
