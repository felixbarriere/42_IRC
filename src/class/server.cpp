#include "../../inc/class/server.hpp"

/***************************************************************************************************************************/
/*                                                Constructors / Destructor                                                */
/***************************************************************************************************************************/

Server::Server() {}

Server::Server(char* portNumberMain, char *password) : portNumber(portNumberMain), _password(password), timeout(TIMEOUT)
{
	showConfig();
	int yes = 1;

	/* Initialiser le socket du serveur (a mettre dans la class server) */
	this->s_socket = socket(AF_INET, SOCK_STREAM, 0);//AF_INET - IPv4
    if (this->s_socket < 0)
		SERVER_ERR("Error during socket creation");

	/* Rendre le socket non-bloquant */
	if (setsockopt(s_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
		SERVER_ERR("setsockopt failed");
	if (fcntl(s_socket, F_SETFL, O_NONBLOCK) == 1)
		SERVER_ERR("Error while rendering the socket non-blocking");

 	/* Configurer l'adresse et le port du serveur */
	memset(&this->s_address, 0, sizeof(this->s_address));
    this->s_address.sin_family = AF_INET;
    this->s_address.sin_port = htons(atoi(this->portNumber));   // convert short integer value for port must be converted into network byte order
    this->s_address.sin_addr.s_addr = INADDR_ANY; //=inet_pton(AF_INET, "0.0.0.0", &s_address.sin_addr);

	/* Lier l'adresse au socket du serveur */
	if (bind(this->s_socket, (struct sockaddr *) &this->s_address, sizeof(this->s_address)) < 0) {
	    SERVER_ERR("Error during bind");   // try above 1024: the first 1024 ports are 'special' and usually need super user privileges to use them
		exit(1);
	}

	/* Écouter les connexions entrantes */
	if (listen(this->s_socket, 5) < 0) //SOMAXCONN (4096 on school machine)   5: backlog définit une longueur maximale jusqu'à laquelle la file des connexions en attente pour sockfd peut croître.
        SERVER_ERR("Error while listening");

	setCommandList();
	_oper.insert(std::pair<std::string, std::string>("admin", "pwd"));
}

Server::~Server()
{
	removeClients();
	close (this->s_socket);
	std::cout << std::endl << "Server closing, see you next time." << std::endl << std::endl;
	// close(this->s_socket);
}

/**********************************************************************************************************/
/*                                                Méthodes                                                */
/**********************************************************************************************************/

void	Server::removeClients() {
	// std::map<int, Client*>::iterator	it = this->_clients.begin();	
	// std::map<int, Client*>::iterator	ite = this->_clients.end();

	size_t clientsNb = _clients.size();

	std::cout << std::endl << "removeClients(void)" << std::endl << std::endl;
	std::cout << std::endl << "_clients.size(): " << _clients.size() << std::endl << std::endl;


	// for (; it != ite; it++) {
		for (size_t i = 0; i < clientsNb; i++) {
			// std::cout << std::endl << "it->second->getC_socket(): " << it->second->getC_socket() << std::endl << std::endl;
			// close(fds[it->second->getC_socket()].fd);
			std::cout << std::endl << "ICI" << std::endl << std::endl;
			
			Client	*tmp = _clients.begin()->second;

			_clients.erase(tmp->getC_socket());

			std::cout << std::endl << "ICI2" << std::endl << std::endl;
			// std::cout << std::endl << "Deleting client #" << it->second->getC_socket() << std::endl << std::endl;

			delete ((tmp));

			std::cout << std::endl << "ICI 3" << std::endl << std::endl;

	}	

	std::cout << std::endl << "_clients.size() 2: " << _clients.size() << std::endl << std::endl;

}

void	Server::acceptClient(void)
{
	int					client_socket;
	struct sockaddr_in	client_address;
	socklen_t			client_len;
	int					yes = 1;

	/* Accepter la connexion entrante du client	 */
	client_len = sizeof(client_address);	
    client_socket = accept(getServerSocket(), (struct sockaddr *) &client_address, &client_len);  //passe de 5 connexions possibles à 4
    
	if (client_socket == -1)
        SERVER_ERR("Error while accepting connexion");
	if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))== -1)
		SERVER_ERR("setsockopt failed");
	if(fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
		SERVER_ERR("Error while rendering the socket non blocking");

	_clients[client_socket] = new Client(client_socket, client_address, this);

	/* Ajouter le socket client à notre tableau de fds */
	fds.push_back(pollfd());			// fds argument, which is a vector of structures pollfd()
	fds.back().fd = client_socket;
	fds.back().events = POLLIN;			// données en attente de lecture.
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
        SERVER_ERR("Error during receipt");
	}
	else if (res == 0) {
		// close(fds[client_socket].fd);
		// delete(_clients[client_socket]);
		// this->_clients.erase(client_socket);

		// SERVER_ERR("Client is disconnected");
	}
	else {
		getUser(client_socket)->setBuffer(getUser(client_socket)->getBuffer().append(buffer_str));	// strcat() works only for char *
		getUser(client_socket)->initMsg();	// à deplacer dans le dernier else. On appelle la methode de creation de commande de la classe Client. Le buffer complet est deja stocké dans l'attribut _buffer de l'instance Client. 
	}
	
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
		/* Préparer le vector de fd pour poll() */
		if (poll(fds.data(), fds.size(), timeout) < 0)
	    {
		    // SERVER_ERR("Error Poll()");
			break ;
		}
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents) 					//revent == 1 : on a recu une requete de irssi
			{
				if (fds[i].revents & POLLIN)		// find the descriptors that returned POLLIN and determine whether it's the listening or the active connection.
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
	}
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

void	Server::createChannel(Client* client, const std::string channel_name) {
	_channels.insert(std::make_pair(channel_name, Channel(client, channel_name)));
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

Client*								Server::getUser(int fd) const {
	std::map<int, Client*>::const_iterator	ret;
	ret = _clients.find(fd);
	
	if (ret == _clients.end())
		return (NULL);

	return (ret->second);
}

Client*								Server::getUserbyNick(std::string nick) const {
	std::map<int, Client*>::const_iterator    it = _clients.begin();
    std::map<int, Client*>::const_iterator    ite = _clients.end();
    
    for (; it != ite; it++)
    {
        if (it->second->getNick() == nick)
            return (it->second);
    }
    return (NULL);
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
	_commandList.insert(std::make_pair("KICK", kick));
	_commandList.insert(std::make_pair("kill", ft_kill));
	_commandList.insert(std::make_pair("LIST", list));
	_commandList.insert(std::make_pair("MODE", mode));
	_commandList.insert(std::make_pair("motd", motd));
	_commandList.insert(std::make_pair("OPERMOTD", opermotd));
	_commandList.insert(std::make_pair("NAMES", names));
	_commandList.insert(std::make_pair("NICK", nick));
	_commandList.insert(std::make_pair("OPER", oper));
	_commandList.insert(std::make_pair("PING", ping));
	_commandList.insert(std::make_pair("USER", user));
	_commandList.insert(std::make_pair("WALLOPS", wallops));
	_commandList.insert(std::make_pair("WHOIS", whoIs));
	_commandList.insert(std::make_pair("PASS", pass));
	_commandList.insert(std::make_pair("PART", part));
	_commandList.insert(std::make_pair("PRIVMSG", privmsg));
	_commandList.insert(std::make_pair("QUIT", quit));
}
