#ifndef	SERVER_HPP
# define SERVER_HPP

# include "../../inc/utils.hpp"

# define SERVER_ERR(err)                                                  	   \
	do                                                                         \
	{                                                                          \
		std::cerr << err << ": " << strerror(errno) << std::endl; 			   \
		exit(1);                                                               \
	} while (0)

class Client;
class Channel;

class Server
{

	public:

		/************ Constructors / Destructor ************/
		Server();
		Server(char* portNumber, char* password);
		~Server();

		/************ Méthodes ************/
		void							init_pollfd_struct();
		void							usePoll();
		void							acceptClient();
		void							receiveRequest(int	client_socket);


		/************ Getters / Setters ************/
		char*								getPortNumber() const ;
		char*								getPassword() const ;
		int									getTimeout() const ;
		int									getServerSocket() const ;
		struct sockaddr_in					getServerAddress() const ;
		std::vector<struct pollfd>			getFds() const ;
		std::map<int, Client*>				getClients() const ;
		Client*								getUser(int fd) const ;
		std::map<std::string, Channel>		getChannels() const ;
		std::map<std::string, std::string>	getOper() const ;

		void							setPortNumber(char * portNumber);

		/************ Attributs ************/
	private:

		char*								portNumber;		// a mettre dans une classe config?
		char*								_password;		// a mettre dans une classe config?
		int									timeout;	
		int									s_socket;
		struct sockaddr_in		 			s_address;
		std::vector<struct pollfd>		 	fds;
		// Client							*client;		//créer un vector ou une map pour pouvoir recevoir plusieurs clients
		std::map<int, Client*>				clients;		//key: fd, value: client
		std::map<std::string, Channel>		_channels;
		std::map<std::string, std::string>	_oper;

};

#endif
