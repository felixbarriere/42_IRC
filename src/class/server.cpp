#include "../../inc/class/server.hpp"

/***************************************************************************************************************************/
/*                                                Constructors / Destructor                                                */
/***************************************************************************************************************************/

Server::Server() {}

Server::Server(char* portNumberMain, char *password) : portNumber(portNumberMain), _password(password), timeout(TIMEOUT)
{
	showConfig();
	int yes = 1;

	// Initialiser le socket du serveur (a mettre dans la class server)
	this->s_socket = socket(AF_INET, SOCK_STREAM, 0);//AF_INET - IPv4
    if (this->s_socket < 0)
		SERVER_ERR("Error during socket creation");

	//rendre le socket non-bloquant
	if (setsockopt(s_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
		SERVER_ERR("setsockopt failed");
	if (fcntl(s_socket, F_SETFL, O_NONBLOCK) == 1)
		SERVER_ERR("Error while rendering the socket non-blocking");

 	// Configurer l'adresse et le port du serveur	(a mettre dans la class server)
	memset(&this->s_address, 0, sizeof(this->s_address));
    this->s_address.sin_family = AF_INET;
    this->s_address.sin_port = htons(atoi(this->portNumber));   // convert short integer value for port must be converted into network byte order
    this->s_address.sin_addr.s_addr = INADDR_ANY; //=inet_pton(AF_INET, "0.0.0.0", &s_address.sin_addr);

	// Lier l'adresse au socket du serveur
	if (bind(this->s_socket, (struct sockaddr *) &this->s_address, sizeof(this->s_address)) < 0)
        SERVER_ERR("Error during bind");   // try above 1024: the first 1024 ports are 'special' and usually need super user privileges to use them

	// Écouter les connexions entrantes
	if (listen(this->s_socket, 5) < 0) //SOMAXCONN (4096 on school machine)   5: backlog définit une longueur maximale jusqu'à laquelle la file des connexions en attente pour sockfd peut croître.
        SERVER_ERR("Error while listening");

	setCommandList();

	_oper.insert(std::pair<std::string, std::string>("admin", "pwd"));

}

Server::~Server()
{
	// std::cout << "DEBUG ===> Destructor, closing server socket" << std::endl << std::endl;
	// close(this->s_socket);
}

/**********************************************************************************************************/
/*                                                Méthodes                                                */
/**********************************************************************************************************/

void	Server::acceptClient(void)
{
	int					client_socket;
	struct sockaddr_in	client_address;
	socklen_t			client_len;
	int					yes = 1;

	// Accepter la connexion entrante du client	
	client_len = sizeof(client_address);	
    client_socket = accept(getServerSocket(), (struct sockaddr *) &client_address, &client_len);  //passe de 5 connexions possibles à 4
    
	if (client_socket == -1)
        SERVER_ERR("Error while accepting connexion");

	// std::cout << "ACCEPT OK, got connexion from " << inet_ntoa(client_address.sin_addr)
	// 	<< " port " << ntohs(client_address.sin_port) << std::endl << std::endl;
		
	if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))== -1)
		SERVER_ERR("setsockopt failed");
	if(fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
		SERVER_ERR("Error while rendering the socket non blocking");

	// utiliser new: "Client *new_client" est simplement la déclaration d'un pointeur de type Client, mais il ne crée pas d'objet Client ni n'alloue de mémoire pour un tel objet ==> comportement indéfini.
	_clients[client_socket] = new Client(client_socket, client_address, this);

	// On ajoute le socket client à notre tableau de fds
	fds.push_back(pollfd());	// fds argument, which is an array of structures of the following form: 
	fds.back().fd = client_socket;
	fds.back().events = POLLIN;		// données en attente de lecture.
	fds.back().revents = POLLIN;
}

void	Server::receiveRequest(int client_socket) {
	char 	buffer[BUFFER_SIZE + 1];
	int		res;

	memset(buffer, 0, BUFFER_SIZE + 1);

	res = recv(client_socket, buffer, BUFFER_SIZE, MSG_DONTWAIT);

	std::string buffer_str(buffer);

	if (buffer_str.size() != 0)
		std::cout << "#" << client_socket << " << " << buffer_str << std::endl;

	if (res == -1) {
		std::cout << "Error during receipt " << res << std::endl;
		// getUser(client_socket)->setBuffer("");
        // SERVER_ERR("Error during receipt");
	}
	else if (res == 0) {
		delete(_clients[client_socket]);
		std::cout << "Client is disconnected " << res << std::endl;
		// SERVER_ERR("Client is disconnected");
	}
	else {
	// else if (res > 0 && (buffer_str.rfind("\n\r")) != (buffer_str.size() - 2)) {
		// std::cout << "Command incomplete: on append() le buffer recu par bouts" <<std::endl;
		getUser(client_socket)->setBuffer(getUser(client_socket)->getBuffer().append(buffer_str));	// strcat() works only for char *
		// getUser(client_socket)->setBuffer(buffer_str);
		getUser(client_socket)->initMsg();	// à deplacer dans le dernier else. On appelle la methode de creation de commande de la classe Client. Le buffer complet est deja stocké dans l'attribut _buffer de l'instance Client. 
	}
	// else 
	// {
	// 	std::cout << "DEBUG ===> recv > 0 : MESSAGE FROM CLIENT"  << std::endl << std::endl;
	// }
	
	buffer_str.clear();
}

void Server::init_pollfd_struct(void)
{
	fds.clear();
	fds.push_back(pollfd());	
	fds.back().fd = s_socket;
	fds.back().events = POLLIN;		
	fds.back().revents = 0;

}

void	Server::usePoll(void)
{
	init_pollfd_struct();
	while(!serv_run)
	{ 
		// Préparer le vector de fd pour poll()
		if (poll(fds.data(), fds.size(), timeout) < 0)	// ou &this->fds[0], mais fds.data() permet de boucler par la suite
	        SERVER_ERR("Error Poll()");
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents) //revent == 1 : on a recu une requete de irssi
			{
				if (fds[i].revents & POLLIN)	// find the descriptors that returned POLLIN and determine whether it's the listening or the active connection.
				{
					if (i == 0)
						acceptClient();
					else
						receiveRequest(fds[i].fd);  //	on envoie le socket du dernier client ajouté: fds[i].fd (qu'on a défini dans acceptClient : this->fds.back().fd = client_socket;)
				}
				else if (fds[i].revents & POLLRDHUP || fds[i].revents & POLLERR)
	        		SERVER_ERR("Error Poll() in FDS");
			}
		}
		// std::cout << std::endl << " Server running (sleep: 1)" << std::endl;
		// sleep(5);
	}
}

void	Server::createChannel(Client* client, const std::string channel_name) {
	_channels.insert(std::make_pair(channel_name, Channel(client)));
}

/*******************************************************************************************************************/
/*                                                Getters / Setters                                                */
/*******************************************************************************************************************/

char*								Server::getPortNumber() const { return (this->portNumber); }
char*								Server::getPassword() const { return (this->_password); }
int									Server::getTimeout() const { return (this->timeout); }
int									Server::getServerSocket() const { return (this->s_socket); }
struct sockaddr_in					Server::getServerAddress() const { return (this->s_address); }
std::vector<struct pollfd>			Server::getFds() const { return (this->fds); }
std::map<int, Client*>				&Server::getClients() { return (_clients); }
std::map<std::string, Channel>		&Server::getChannels() { return (_channels); }
std::map<std::string, fct_cmd>		&Server::getCommandList() { return (_commandList); }
std::map<std::string, std::string>	&Server::getOper() { return (_oper); }

Client*	Server::getUser(int fd) const {
	std::map<int, Client*>::const_iterator	ret;
	ret = _clients.find(fd);
	if (ret == _clients.end())
		return (NULL);
	return (ret->second);
}

bool	Server::nickIsUsed(std::string str) const {
	std::cout << "DEBUG ===> nickIsUsed test"   << std::endl;

	std::map<int, Client*>::const_iterator	it = _clients.begin();
	std::map<int, Client*>::const_iterator	ite = _clients.end();
	for (; it != ite ; it++)
	{
		std::cout << "DEBUG ===> existing nicknames: " << (it->second->getNick()) << std::endl;

		if (str == it->second->getNick())
			return (true);
	}
	return (false);
}

void	Server::setPortNumber(char *portNumber) { this->portNumber = portNumber; }

void Server::setCommandList() {
	_commandList.insert(std::make_pair("ADDMOTD", addmotd));
	_commandList.insert(std::make_pair("ADDOMOTD", addomotd));
	_commandList.insert(std::make_pair("CHGNAME", chgname));
	_commandList.insert(std::make_pair("GLOBOPS", globops));
	_commandList.insert(std::make_pair("CHGHOST", chgname));
	_commandList.insert(std::make_pair("CHGNAME", chgname));
	_commandList.insert(std::make_pair("JOIN", join));
	_commandList.insert(std::make_pair("LIST", list));
	_commandList.insert(std::make_pair("MODE", mode));
	_commandList.insert(std::make_pair("MOTD", motd));
	_commandList.insert(std::make_pair("OPERMOTD", opermotd));
	_commandList.insert(std::make_pair("NAMES", names));
	_commandList.insert(std::make_pair("NICK", nick));
	_commandList.insert(std::make_pair("PING", ping));
	_commandList.insert(std::make_pair("USER", user));
	_commandList.insert(std::make_pair("WALLOPS", wallops));
	_commandList.insert(std::make_pair("WHOIS", whoIs));
	_commandList.insert(std::make_pair("PASS", pass));
	_commandList.insert(std::make_pair("PART", part));
	_commandList.insert(std::make_pair("PRIVMSG", privmsg));
	_commandList.insert(std::make_pair("QUIT", quit));
}
