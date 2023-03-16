#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../../inc/utils.hpp"

class	Channel {

	public:

		/*** MEMBER FUNCTIONS ***/

		Channel(Client*);
		~Channel();

		Client*					getCreator() const;
		std::vector<Client*>&	getMembers();
		std::map<char, bool>&	getModes();
		std::string				getPwd() const;
		int						getLimit() const;

		void	setPwd(const std::string);
		void	setLimit(int);

		void	addMember(Client*);
		void	removeMember(Client*);
		void	broadcast(Client*, std::string);

	private:

		/*** MEMBER OBJECTS ***/

		Client*					_creator;
		std::vector<Client*>	_members;
		std::map<char, bool>	_modes;
		std::string				_pwd;
		int						_limit;

};

#endif
