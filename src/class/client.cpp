#include "utils.hpp"

Client::Client() 
{	std::cout << "DEBUG ===> Default constructor CLIENT" << std::endl << std::endl;	}

Client::Client(int client_socket, struct sockaddr_in client_address) : c_socket(client_socket), c_address(client_address)
{
	std::cout << "DEBUG ===> Constructor CLIENT" << std::endl << std::endl;
}

Client::~Client() 
{	std::cout << "DEBUG ===> Destructor CLIENT" << std::endl << std::endl;	}
