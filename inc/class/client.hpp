#ifndef	CLIENT_HPP
#define CLIENT_HPP

# include "../utils.hpp"

class Message;
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
		void	sendMsg(std::string str);
		//bool conn(std::string, int);
    // bool send_data(std::string data);
		//https://www.binarytides.com/code-a-simple-socket-client-class-in-c/

		/************ Getters ************/

		int 					getC_socket() const ;
		std::string			 	getSockaddr_in() const;
		std::string 			getBuffer() const ;
		Channel					*getChannel() const ;
		std::string				getNick() const ;
		std::string				getUser() const ;
		std::string		 		getHostname() const;
		std::map<char, bool>	getModes() const ;
		bool					getOper() const ;
		
		/************ Setters ************/

		void	setChannel(Channel *channel);
		void	setBuffer(const std::string str);
		void	setNick(const std::string nick);
		void	setUser(const std::string user);
		void	setHostname(std::string str);	//utile?
		void	setOper(const bool oper);

	private:
		//pour stocker l'integralite du message recu

		/************ Attributs ************/

		bool								_welcomeMsg;	//le welcome_message a-t-il été envoyé?
		std::string							_buffer; //pour stocker l'integralite du message recu
		std::string							_user;
		std::string							_nick;
		std::string							_hostname;
		int									_c_socket;
		std::string 						_c_address;
		// std::map<std::string, std::string>	_infosClient;	//Supprimer. infos renvoyées par IRSSI lors de la connexion.
		// std::map<char, bool>				_modes;	
		Message								*_message;
		std::map<std::string, std::string>	_commands;
		Channel								*_channel;	
		std::map<char, bool>				_modes;
		bool								_oper;

};

#endif
