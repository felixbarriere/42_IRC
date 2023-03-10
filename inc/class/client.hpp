#ifndef	CLIENT_HPP
#define CLIENT_HPP

# include "../utils.hpp"

class Message;
class Channel;
class Server;

class Client
{

	public:

		/************ Constructors / Destructor ************/

		Client();
		Client(const Client &src);
		Client &operator=(const Client &rhs);
		Client(int client_socket, struct sockaddr_in client_address, Server *server);
		~Client();

		/************ Méthodes ************/

		void		addBuff(char buff_msg);
		void		welcome_msg();
		void		initMsg();
		void		sendMsg(std::string str);
		void		sendMsg2(std::string str);
		std::string	getPrefix() const;
		//bool conn(std::string, int);
    // bool send_data(std::string data);
		//https://www.binarytides.com/code-a-simple-socket-client-class-in-c/

		/************ Getters ************/

		int 					getC_socket() const ;
		std::string			 	getSockaddr_in() const;
		std::string 			getBuffer() const ;
		Channel					*getChannel() const ;
		Server					*getServer() const ;
		std::string				getNick() const ;
		std::string				getUser() const ;
		std::string				getRealName() const ;
		std::string		 		getHostname() const;
		std::map<char, bool>	&getModes();
		Message					*getMessage() const ;
		bool					getWelcome() const ;
		bool					getAuthorized() const ;
		
		/************ Setters ************/

		void	setChannel(Channel *channel);
		void	setBuffer(const std::string str);
		void	setNick(const std::string nick);
		void	setUser(const std::string user);
		void	setRealName(const std::string realName);
		void	setHostname(std::string str);	//utile?
		void	setAuthorized(bool);
		void	setMessage(Message *message);

	private:
		//pour stocker l'integralite du message recu

		/************ Attributs ************/

		bool								_welcomeMsg;	//le welcome_message a-t-il été envoyé?
		bool								_authorized;	//le welcome_message a-t-il été envoyé?
		std::string							_buffer; //pour stocker l'integralite du message recu
		std::string							_user;
		std::string							_nick;
		std::string							_realName;
		std::string							_hostname;
		int									_c_socket;
		std::string 						_c_address;
		// std::map<std::string, std::string>	_infosClient;	//Supprimer. infos renvoyées par IRSSI lors de la connexion.
		std::map<std::string, std::string>	_commands;
		std::map<char, bool>				_modes;
		Message								*_message;
		Channel								*_channel;	
		Server								*_server;

};

#endif
