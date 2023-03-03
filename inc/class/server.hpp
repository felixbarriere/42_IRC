#ifndef	SERVER_HPP
#define SERVER_HPP

#include "utils.hpp"

typedef void (*fct_cmd)();

#define SERVER_ERR(err)                                                  	   \
	do                                                                         \
	{                                                                          \
		std::cerr << err << ": " << strerror(errno) << std::endl; 			   \
		exit(1);                                                               \
	} while (0)

class Client;

class Server
{
	public:

		/************ Constructors / Destructor ************/
		Server();
		Server(char* portNumber, char* password);
		~Server();

		/************ Méthodes ************/
		void						init_pollfd_struct(void);
		void						usePoll(void);
		void						acceptClient(void);
		void						receiveRequest(int	client_socket);


		/************ Getters / Setters ************/
		char*							getPortNumber(void) const;
		char*							getPassword(void) const;
		int								getTimeout(void) const;
		int								getServerSocket(void) const;
		struct sockaddr_in				getServerAddress(void)const;
		std::vector<struct pollfd>		getFds(void) const;
		std::map<int, Client*>			getClients(void) const;
		std::map<std::string, fct_cmd>	getCommandList(void) const; 
		Client*							getUser(int fd) const;

		void							setPortNumber(char * portNumber);
		void							setCommandList(void);

		/************ Attributs ************/
	private:

		char*							portNumber;		// a mettre dans une classe config?
		char*							_password;		// a mettre dans une classe config?
		int								timeout;	
		int								s_socket;
		struct sockaddr_in 				s_address;
		std::vector<struct pollfd> 		fds;
		// Client						*client;		//créer un vector ou une map pour pouvoir recevoir plusieurs clients
		std::map<int, Client*>			clients;		//key: fd, value: client
		std::map<std::string, fct_cmd>	_commandList; 
};

#endif