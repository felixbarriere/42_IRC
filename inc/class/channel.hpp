#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../../inc/utils.hpp"

class	Channel {

	public:

		/*** MEMBER FUNCTIONS ***/

		Channel() {}

		Channel(Client *creator):
			_creator(creator) {
			_members.push_back(_creator);
			_modes.insert(std::pair<char, bool>('k', false));
			_modes.insert(std::pair<char, bool>('l', false));
			_modes.insert(std::pair<char, bool>('m', false));
			_modes.insert(std::pair<char, bool>('n', false));
			_modes.insert(std::pair<char, bool>('p', false));
			_modes.insert(std::pair<char, bool>('s', false));
		}

		~Channel() {}

		Client	*getCreator() const {
			return (_creator);
		}

		const std::vector<Client*>	&getMembers() const {
			return (_members);
		}

		const std::map<char, bool>	&getModes() const {
			return (_modes);
		}

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

	private:

		/*** MEMBER OBJECTS ***/

		Client					*_creator;
		std::vector<Client*>	_members;
		std::map<char, bool>	_modes;

};

#endif
