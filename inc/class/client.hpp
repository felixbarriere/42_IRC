#ifndef	CLIENT_HPP
#define CLIENT_HPP

# include "../utils.hpp"

class Message;
class Channel;
class Server;

class Client {

	public:

		/************ Constructors / Destructor ************/

		Client();
		Client(const Client&);
		Client &operator=(const Client&);
		Client(int, struct sockaddr_in, Server*);
		~Client();

		/************ Méthodes ************/

		void		welcome_msg();
		void		initMsg();
		void		sendMsg(std::string, Client*);
		std::string	getPrefix() const;
		void		addMode(char);
		void		removeMode(char);
		bool		checkChannelName(const std::string);
		void		removeChannelName(std::string);

		//bool conn(std::string, int);
	    // bool send_data(std::string data);
		//https://www.binarytides.com/code-a-simple-socket-client-class-in-c/

		/************ Getters ************/

		int 					getC_socket() const ;
		std::string			 	getSockaddr_in() const;
		std::string 			getBuffer() const ;
		Channel*				getChannel();
		const std::string		getChannelName() const;  //plus de sens
		std::vector<std::string>&	getChannelsNames();  //plus de sens
		Server*					getServer() const ;
		std::string				getNick() const ;
		std::string				getUser() const ;
		std::string				getRealName() const ;
		std::string		 		getHostname() const;
		std::map<char, bool>&	getModes();
		std::string				getModesString();
		Message*				getMessage() const ;
		bool					getWelcome() const ;
		bool					getAuthorized() const ;
		
		/************ Setters ************/

		// void	setChannel(Channel *channel);
		// void	setChannelName(const std::string str); //plus de sens

		void	setBuffer(const std::string);
		void	setNick(const std::string);
		void	setUser(const std::string);
		void	setRealName(const std::string);
		void	setHostname(std::string);	//utile?
		void	setAuthorized(bool);
		void	setMessage(Message*);

	private:

		/************ Attributs ************/

		bool								_welcomeMsg;	//le welcome_message a-t-il été envoyé?
		bool								_authorized;	//le welcome_message a-t-il été envoyé?
		std::string							_buffer;		//pour stocker l'integralite du message recu
		std::string							_user;
		std::string							_nick;
		std::string							_realName;
		std::string							_hostname;
		int									_c_socket;
		std::string 						_c_address;
		std::map<std::string, std::string>	_commands;
		std::map<char, bool>				_modes;
		Message*							_message;
		Channel*							_channel;	
		std::string							_channelName;	
		std::vector<std::string>			_channelsNames;	
		Server*								_server;

};

std::ostream& operator<<(std::ostream& os, const std::map<char, bool>& m);

#endif
