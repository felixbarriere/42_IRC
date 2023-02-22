#ifndef	SERVER_HPP
#define SERVER_HPP


// #include "utils.hpp"


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
		//void						init_pollfd_struct(std::vector<struct pollfd> &fds);
		void						usePoll(void);
		void						acceptClient(void);
		void						receiveRequest(int	client_socket);


		/************ Getters / Setters ************/
		char*						getPortNumber(void);
		char*						getPassword(void);
		int							getTimeout(void);
		int							getServerSocket(void);
		struct sockaddr_in			getServerAddress(void);
		std::vector<struct pollfd>	getFds(void);
		std::map<int, Client*>		getClients(void);
		Client*						getUser(int fd);

		void						setPortNumber(char * portNumber);


		/************ Attributs ************/
	private:

		char*						portNumber;		// a mettre dans une classe config?
		char*						password;		// a mettre dans une classe config?
		int							timeout;	
		int							s_socket;
		struct sockaddr_in 			s_address;
		std::vector<struct pollfd> 	fds;
		// Client						*client;		//créer un vector ou une map pour pouvoir recevoir plusieurs clients
		std::map<int, Client*>		clients;		//key: fd, value: client
};

#endif