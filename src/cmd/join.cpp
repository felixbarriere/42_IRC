#include "../../inc/utils.hpp"

void	join(Server* server, Client* client) {
	if (!client->getMessage()->getParams().size())
		client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Not enough parameters", client);
	else {
		const char*					channels = client->getMessage()->getParams()[0].c_str();
		char*						ptr = strtok((char*)channels, ",");
		std::vector<std::string>	channel_names;
		while (ptr) {
			if ((std::string)ptr != "")
				channel_names.push_back(std::string(ptr));
			ptr = strtok(NULL, ",");
		}
		for (unsigned int i = 0; i < channel_names.size(); i++) {
			if (channel_names[i][0] != '#' && channel_names[i][0] != '&' && channel_names[i][0] != '+' && channel_names[i][0] != '!')
				channel_names[i] = "#" + channel_names[i];
			std::map<std::string, Channel>::iterator	it = server->getChannels().find(channel_names[i]);
			if (it == server->getChannels().end())
				server->createChannel(client, channel_names[i]);
			else {
				it->second.addMember(client);
				client->getChannelsNames().push_back(channel_names[i]);
				it->second.broadcast(client, "JOIN " + it->first);
			}
			client->sendMsg("JOIN " + channel_names[i], client);
		}
	}
}

