#include "utils.hpp"

Client::Client(): _c_socket(-1)
{	
	std::cout << "DEBUG ===> Default constructor CLIENT" << std::endl << std::endl;
}

Client::Client(int client_socket, struct sockaddr_in client_address) : _c_socket(client_socket), _c_address(client_address)
{
	std::cout << "DEBUG ===> Constructor CLIENT" << std::endl << std::endl;
}

Client::Client(const Client &src): _c_socket(-1)
{
	(void)src;
}

Client &Client::operator=(const Client &rhs)
{
	(void)rhs;
	return *this;
}

Client::~Client() 
{	
	close(this->_c_socket);
	std::cout << "DEBUG ===> Destructor CLIENT" << std::endl << std::endl;
}

/************ Méthodes ************/
// void Client::addBuff(char buff_msg)
// {
// 	if (this->_buffer.find(_buffer) != std::string::npos)
// 		this->_buffer += _buffer;
// 	else
// 		return ;
// }


/************ Getters / Setters ************/
int Client::getC_socket() const
{
	return (this->_c_socket);
}

struct sockaddr_in Client::getSockaddr_in() const
{
	return (this->_c_address);
}

std::string Client::getBuffer() const
{
	return (this->_buffer);
}

void Client::setBuffer(std::string str)
{
	this->_buffer = str;
}


