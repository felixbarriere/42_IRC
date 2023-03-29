#include "../../inc/class/channel.hpp"

Channel::Channel(Client* client, const std::string channelName):
	_creator(client),
	_pwd(""),
	_limit(0) {
	_modes.insert(std::pair<char, bool>('k', false));
	_modes.insert(std::pair<char, bool>('l', false));
	_modes.insert(std::pair<char, bool>('m', false));
	_modes.insert(std::pair<char, bool>('n', false));
	_modes.insert(std::pair<char, bool>('p', false));
	_modes.insert(std::pair<char, bool>('s', false));
	addMember(client);
	// client->setChannel(this);
	// client->setChannelName(channelName); //plus de sens
	client->getChannelsNames().push_back(channelName);
	client->sendMsg("JOIN ", client);

}

Channel::~Channel() {}

// std::string				Channel::getName() const { return (_name); }
Client*					Channel::getCreator() const { return (_creator); }
std::vector<Client*>&	Channel::getMembers() { return (_members); }
std::map<char, bool>&	Channel::getModes() { return (_modes); }
std::string				Channel::getPwd() const { return (_pwd); }
int						Channel::getLimit() const { return (_limit); }

void	Channel::setPwd(const std::string pwd) { _pwd = pwd; }
void	Channel::setLimit(int limit) { _limit = limit; }

void	Channel::addMember(Client* client) {
	_members.push_back(client);
}

void	Channel::removeMember(Client* client) {
	if (client == NULL)
		return ; 
	std::vector<Client*>::iterator	it = _members.begin();
	while (it != _members.end()){
		if (*it == client) {
			_members.erase(it);
			return ;
		}
		it++;
	}
}

std::string Channel::getMemberName(std::string targetNick) {
	std::string result = "";
	for (std::vector<Client*>::iterator it = _members.begin(); it != _members.end(); ++it) {
		if ((*it)->getNick() == targetNick) {
			result = (*it)->getNick();
			break;
		}
	}
  	return (result);
}

void	Channel::broadcast(Client* sender, std::string msg) {
	for (long unsigned int i = 0; i < _members.size(); i++) {
		if (_members[i] != sender)
			_members[i]->sendMsg(msg, sender);
	}
}

bool	Channel::ifMemberbyNick(std::string nick) {
	std::vector<Client*>::iterator    it = _members.begin();
    std::vector<Client*>::iterator    ite = _members.end();
    
    for (; it != ite; it++)
    {
        if ((*it)->getNick() == nick)
            return (true);
    }
    return (false);
}
