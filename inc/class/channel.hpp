#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../../inc/utils.hpp"

class	Channel {

	public:

		/*** MEMBER FUNCTIONS ***/

		Channel(Client *client):
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
		}

		~Channel() {}

		Client					*getCreator() const { return (_creator); }
		std::vector<Client*>	&getMembers() { return (_members); }
		std::map<char, bool>	&getModes() { return (_modes); }
		std::string				getPwd() const { return (_pwd); }
		int						getLimit() const { return (_limit); }

		void	setPwd(const std::string pwd) { _pwd = pwd; }
		void	setLimit(int limit) { _limit = limit; }

		void	addMember(Client *client) {
			_members.push_back(client);
		}

		void	removeMember(Client *client) {
			std::vector<Client*>::iterator	it = _members.begin();
			while (it != _members.end()){
				if (*it == client) {
					_members.erase(it);
					return ;
				}
				it++;
			}
		}

		void	broadcast(Client *client, std::string msg) {
			for (long unsigned int i = 0; i < _members.size(); i++) {
				if (_members[i] != client)
					_members[i]->sendMsg(msg);
			}
		}

	private:

		/*** MEMBER OBJECTS ***/

		Client					*_creator;
		std::vector<Client*>	_members;
		std::map<char, bool>	_modes;
		std::string				_pwd;
		int						_limit;

};

#endif
