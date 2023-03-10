#include "../../inc/utils.hpp"

/***************************************************************************************************************************/
/*                                                Constructors / Destructor                                                */
/***************************************************************************************************************************/

Client::Client(): _c_socket(-1)
{	
	// std::cout << "Default constructor CLIENT" << std::endl << std::endl;
}

Client::Client(int client_socket, struct sockaddr_in client_address, Server *server):
	_welcomeMsg(false),
	_authorized(false),
	_user(),
	_nick(),
	_c_socket(client_socket),
	_channel(NULL),
	_server(server)
{
	// std::cout << "Constructor CLIENT" << std::endl << std::endl;

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

	_modes.insert(std::pair<char, bool>('d', false));
	_modes.insert(std::pair<char, bool>('e', false));
	_modes.insert(std::pair<char, bool>('i', false));
	_modes.insert(std::pair<char, bool>('o', false));
	_modes.insert(std::pair<char, bool>('q', false));
	_modes.insert(std::pair<char, bool>('t', false));
	_modes.insert(std::pair<char, bool>('u', false));
	_modes.insert(std::pair<char, bool>('v', false));
	_modes.insert(std::pair<char, bool>('w', false));

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
	// std::cout << "DEBUG ===> Destructor CLIENT" << std::endl << std::endl;
}

/**********************************************************************************************************/
/*                                                Méthodes                                                */
/**********************************************************************************************************/

void	Client::sendMsg(std::string str)
{
	if (getAuthorized() == false)
		return ;

	ssize_t 		ret = 0;	//number of bytes sent
	std::string		toSend = ":" + _message->getPrefix() + str;
	
	std::cout << "#" << _c_socket <<  " >> " << toSend << std::endl;
	toSend += "\r\n";

	ret = send(_c_socket, toSend.c_str(), toSend.length(), MSG_NOSIGNAL);
	if (ret == -1)
		std::cout << "send() failed " << std::endl;
	// std::cout << "ret:  " << ret << std::endl;
	
	toSend.clear();
}

void	Client::welcome_msg()
{
	this->_welcomeMsg = true;

	std::string		str;

	// str = "001 " + this->_nick +": Welcome to the Internet Relay Network " + this->_nick + "!" + this->_user + "@" + this->_hostname;
	str = RPL_WELCOME + this->_nick + " : Welcome to the Internet Relay Network " + this->_message->getPrefix();
	// std::cout << "DEBUG == > STR: " << str << std::endl;
	this->sendMsg(str);

	str = RPL_YOURHOST + this->_nick + " : Your host is " + NAME + ", running version " + VERSION;
	this->sendMsg(str);

	str = RPL_CREATED + this->_nick +" : This server was create " + "now";	//ctime(&(time(0)))
	this->sendMsg(str);
	
	str = RPL_MYINFO + this->_nick + " " + NAME + " " + VERSION;
	this->sendMsg(str);

	std::ifstream	ifs;
	if (getModes().find('o')->second)
		ifs.open("src/motd/omotd.txt");
	else
		ifs.open("src/motd/motd.txt");
	std::stringstream	s;
	s << ifs.rdbuf();
	sendMsg(s.str());

}

void	Client::initMsg()  //changer nom function
{
	// std::cout << "DEBUG == > BUFFER CLIENT:" << std::endl << this->getBuffer() << std::endl;
	_message->createMessage();	
	if (!_welcomeMsg)
		welcome_msg();
	if (!_buffer.empty())
		_buffer.clear();
}

std::string	Client::getPrefix() const
{
	return (getMessage()->getPrefix());
	// std::string	prefix = "" + _nick;
	// if (_user.size())
	// 	prefix += "!" + _user;
	// if (_hostname.size())
	// 	prefix += "@" + _hostname;
	// else
	// 	prefix += "@" + _c_address;
	// return (prefix);
}

/*******************************************************************************************************************/
/*                                                Getters / Setters                                                */
/*******************************************************************************************************************/


/************ Getters ************/

int						Client::getC_socket() const { return (_c_socket); }
std::string				Client::getSockaddr_in() const { return (_c_address); }
std::string				Client::getBuffer() const { return (_buffer); }
Channel					*Client::getChannel() const { return (_channel); }
Server					*Client::getServer() const { return (_server); }
std::string				Client::getNick() const { return (_nick); }
std::string				Client::getUser() const { return (_user); }
std::string				Client::getRealName() const { return (_realName); }
std::string 			Client::getHostname() const { return (_hostname); }
std::map<char, bool>	&Client::getModes() { return (_modes); }
Message					*Client::getMessage() const { return (_message); }
bool					Client::getWelcome() const { return (_welcomeMsg); }
bool					Client::getAuthorized() const { return (_authorized); }


/************ Setters ************/

void	Client::setBuffer(const std::string str) { _buffer = str; }
void	Client::setChannel(Channel *channel) { _channel = channel; }
void	Client::setNick(const std::string nick) { _nick = nick; }
void	Client::setUser(const std::string user) { _user = user; }
void	Client::setRealName(const std::string realName) { _realName = realName; }
void 	Client::setHostname(std::string str) { _hostname = str; }
void	Client::setAuthorized(bool isAuth) { _authorized = isAuth; }
void	Client::setMessage(Message *message) { _message = message; }
