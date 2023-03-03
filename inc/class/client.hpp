#ifndef	CLIENT_HPP
#define CLIENT_HPP

# include "../../inc/utils.hpp"

class Channel;

class Client
{

	public:

		/************ Constructors / Destructor ************/

		Client();
		Client(const Client &src);
		Client &operator=(const Client &rhs);
		Client(int client_socket, struct sockaddr_in client_address);
		~Client();

		/************ Méthodes ************/

		void	addBuff(char buff_msg);
		void	welcome_msg();
		void	createCommandList();

		/************ Getters ************/

		int 					getC_socket() const ;
		struct sockaddr_in	 	getSockaddr_in() const ;
		std::string 			getBuffer() const ;
		Channel					*getChannel() const ;
		std::string				getNick() const ;
		std::string				getUser() const ;
		std::map<char, bool>	getModes() const ;
		bool					getOper() const ;
		
		/************ Setters ************/

		void	setChannel(Channel *channel);
		void	setBuffer(const std::string str);
		void	setNick(const std::string nick);
		void	setUser(const std::string user);
		void	setOper(const bool oper);

	private:

		/************ Attributs ************/

		std::string							_buffer; //pour stocker l'integralite du message recu
		std::string							_user;
		std::string							_nick;
		int									_c_socket;
		struct sockaddr_in 					_c_address;
		std::map<std::string, std::string>	_commands;
		Channel								*_channel;	
		std::map<char, bool>				_modes;
		bool								_oper;

};

#endif
