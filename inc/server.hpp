#include <errno.h>

#define SERVER_ERR(err)                                                  	   \
	do                                                                         \
	{                                                                          \
		std::cerr << err << ": " << strerror(errno) << std::endl; 			   \
		exit(1);                                                               \
	} while (0)

class server
{
	public:

		server();
		server(char* portNumber);
		~server();

		void	setPortNumber(char * portNumber);
	private:
		char *	portNumber;
};