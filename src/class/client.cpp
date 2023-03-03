#include "utils.hpp"

/***************************************************************************************************************************/
/*                                                Constructors / Destructor                                                */
/***************************************************************************************************************************/

Client::Client(): _c_socket(-1)
{	
	std::cout << "Default constructor CLIENT" << std::endl << std::endl;
}

Client::Client(int client_socket, struct sockaddr_in client_address) : _c_socket(client_socket), _welcomeMsg(false)
{
	std::cout << "Constructor CLIENT" << std::endl << std::endl;

	this->_c_address = inet_ntoa(client_address.sin_addr);
	
	// http://manpagesfr.free.fr/man/man3/getnameinfo.3.html
	// int getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen, int flags);

	char	host[NI_MAXHOST];     // Client's remote name
	memset(host, 0, NI_MAXHOST);
	if (getnameinfo((const struct sockaddr *)&client_address, sizeof(client_address), host, NI_MAXHOST, NULL, 0, 0) != 0)
		SERVER_ERR("Error getnameinfo()");
	_hostname = host;

	// instancier Message message;
	this->_message = new Message(this);	//envoyer un pointeur de this



}

Client::Client(const Client &src): _c_socket(-1)	//a changer si on utilise le const par copy
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

/**********************************************************************************************************/
/*                                                Méthodes                                                */
/**********************************************************************************************************/

// void Client::addBuff(char buff_msg)
// {
// 	if (this->_buffer.find(_buffer) != std::string::npos)  // c'est pas ce qu'on fait dans la condition de receiveRequest?
// 		this->_buffer += _buffer;
// 	else
// 		return ;
// }

void	Client::sendMsg(std::string str)
{
	ssize_t 		ret = 0;	//number of bytes sent

	// std::cout << std::endl << "DEBUG == > sending... " << std::endl;
	// std::cout << "DEBUG == > str.size(): " << str.size() << std::endl;
	// std::cout << "DEBUG == > ret: " << ret << std::endl;
	// std::cout << "DEBUG == > this->_c_socket: " << this->_c_socket << std::endl;

	// ssize_t send(int socket, const void *buffer, size_t length, int flags);
	ret = send(this->_c_socket, str.c_str(), str.length(), MSG_NOSIGNAL);
	if (ret == -1)
		SERVER_ERR("send() failed");
	
	// std::cout << "DEBUG == > ret after send(): " << ret << std::endl;

	str.clear();
}

void	Client::welcome_msg()
{
	this->_welcomeMsg = true;

	// this->sendMsg("test\r\n");
	std::string		str;
	
	// "<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]"
	str = "001 " + this->_nick +": Welcome to the Internet Relay Network " + this->_nick + "!" + this->_user + "@" + this->_hostname + "\r\n";
	std::cout << "DEBUG == > STR: " << str << std::endl;
	this->sendMsg(str);
	// "<client> :Your host is <servername>, running version <version>"
	str = "002 " + this->_nick + ": Your host is " + NAME + ", running version " + VERSION + "\r\n";
	this->sendMsg(str);
	// "<client> :This server was created <datetime>"
	str = "003 " + this->_nick +": This server was create " + "now"  + "\r\n";	//ctime(&(time(0)))
	this->sendMsg(str);
	
	// "<client> <servername> <version> <available user modes> <available channel modes> [<channel modes with a parameter>]"
	str = "004 " + this->_nick + " " + NAME + " " + VERSION  + "\r\n";
	this->sendMsg(str);
	this->sendMsg(MOTD);

}

void	Client::createCommandList()
{
	std::cout << "DEBUG == > BUFFER CLIENT:" << std::endl << this->getBuffer() << std::endl;

	this->_message->createMessage(this->getBuffer());	

	if (this->_welcomeMsg == false)
		this->welcome_msg();
	if (this->_buffer.empty() == true)
		this->_buffer.clear();
}



/*******************************************************************************************************************/
/*                                                Getters / Setters                                                */
/*******************************************************************************************************************/

int Client::getC_socket() const
{
	return (this->_c_socket);
}

std::string Client::getSockaddr_in() const
{
	return (this->_c_address);
}

std::string Client::getBuffer() const
{
	return (this->_buffer);
}

std::string Client::getUser() const { return (this->_user); }
std::string Client::getNick() const { return (this->_nick); }
std::string Client::getHostname() const { return (this->_hostname); }

void 		Client::setBuffer(std::string str)
{
	this->_buffer = str;
}

void 		Client::setUser(std::string str) { this->_user = str;	}
void 		Client::setNick(std::string str) { this->_nick = str;	}
void 		Client::setHostname(std::string str) { this->_hostname = str;	}

