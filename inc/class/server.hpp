#ifndef	SERVER_HPP
#define SERVER_HPP


// #include "utils.hpp"


#define SERVER_ERR(err)                                                  	   \
	do                                                                         \
	{                                                                          \
		std::cerr << err << ": " << strerror(errno) << std::endl; 			   \
		exit(1);                                                               \
	} while (0)

class Server
{
	public:

		Server();
		Server(char* portNumber, char* password);
		~Server();

		char*						getPortNumber(void);
		char*						getPassword(void);
		int							getTimeout(void);
		int							getServerSocket(void);
		struct sockaddr_in			getServerAddress(void);
		std::vector<struct pollfd>	getFds(void);

		void						setPortNumber(char * portNumber);





	private:

		char*						portNumber;		// a mettre dans une classe config?
		char*						password;		// a mettre dans une classe config?
		int							timeout;	
		int							s_socket;
		struct sockaddr_in 			s_address;
		std::vector<struct pollfd> 	fds;
};

#endif