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
		int							getServerSocket(void);
		struct sockaddr_in			getServerAddress(void);
		std::vector<struct pollfd>	getFds(void);

		void						setPortNumber(char * portNumber);


	private:

		char*						portNumber;
		char*						password;
		int							timeout;
		int							s_socket;		// private?
		struct sockaddr_in 			s_address;		// private?
		std::vector<struct pollfd> 	fds;
};

#endif