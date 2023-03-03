#include "../../inc/utils.hpp"

void	chgname(Client *changer, Client *changee, const std::string name) {
	if (!(changer->getOper()))
		return ;
	changee->setUser(name);
}
