#ifndef	SERVER_HPP
# define SERVER_HPP

# include "../utils.hpp"

class Server;
class Client;
typedef void (*fct_cmd)(Server *server, Client *client);

#define SERVER_ERR(err)                                                  	   \
	do                                                                         \
	{                                                                          \
		std::cerr << err << ": " << strerror(errno) << std::endl; 			   \
	} while (0)
// 		==> exit(1);


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
		void								init_pollfd_struct();
		void								usePoll();
		void								acceptClient();
		void								removeClients(void);
		void								receiveRequest(int	client_socket);
		bool								nickIsUsed(std::string str) const;

		/************ Getters / Setters ************/
		std::map<std::string, fct_cmd>		&getCommandList(); 
		char*								getPortNumber() const ;
		char*								getPassword() const ;
		int									getTimeout() const ;
		int									getServerSocket() const ;
		struct sockaddr_in					getServerAddress() const ;
		std::vector<struct pollfd>			getFds() const ;
		std::map<int, Client*>				&getClients();
		Client*								getUser(int fd) const ;
		std::map<std::string, Channel>		&getChannels();
		std::map<std::string, std::string>	&getOper();

		void	setPortNumber(char *portNumber);
		void	setCommandList();

		/************ Attributs ************/
	private:

		std::map<std::string, fct_cmd>		_commandList; 
		char*								portNumber;		// a mettre dans une classe config?
		char*								_password;		// a mettre dans une classe config?
		int									timeout;	
		int									s_socket;
		struct sockaddr_in		 			s_address;
		std::vector<struct pollfd>		 	fds;
		std::map<int, Client*>				_clients;		//key: fd, value: client
		std::map<std::string, Channel>		_channels;
		std::map<std::string, std::string>	_oper;

};

#endif
