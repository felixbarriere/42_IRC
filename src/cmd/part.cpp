#include "../../inc/utils.hpp"

void	part(Server* server, Client* client) {
	if (client->getMessage()->getParams().size() == 0)
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Error need more params.", client);
	else {
		const char*					channels = client->getMessage()->getParams()[0].c_str();
		char*						ptr = strtok((char*)channels, ",");
		std::vector<std::string>	channel_names;
		while (ptr) {
			channel_names.push_back(std::string(ptr));
			ptr = strtok(NULL, ",");
		}
		for (unsigned int i = 0; i < channel_names.size(); i++) {
			for (std::map<std::string, Channel>::iterator it = server->getChannels().begin(); it != server->getChannels().end(); it++) {
				if (it->first == channel_names[i]) {
					for (std::vector<std::string>::iterator itt = client->getChannelsNames().begin(); itt != client->getChannelsNames().end(); itt++) {
						if (*itt == channel_names[i]) {
							client->sendMsg("PART " + it->first, client);
							it->second.removeMember(client);
							it->second.broadcast(client, "PART " + it->first);
							break ;
						}
					}
				}
			}
		}
	}
}
