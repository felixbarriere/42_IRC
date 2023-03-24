#include "../../inc/class/server.hpp"

/***************************************************************************************************************************/
/*                                                Constructors / Destructor                                                */
/***************************************************************************************************************************/

Server::Server() {}

Server::Server(char* portNumberMain, char *password):
	portNumber(portNumberMain),
	_password(password),
	timeout(TIMEOUT) {
	showConfig();
	int yes = 1;
	// Initialiser le socket du serveur (a mettre dans la class server)
	s_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (s_socket < 0)
		SERVER_ERR("Error during socket creation");
	// Rendre le socket non-bloquant
	if (setsockopt(s_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
		SERVER_ERR("setsockopt failed");
	if (fcntl(s_socket, F_SETFL, O_NONBLOCK) == 1)
		SERVER_ERR("Error while rendering the socket non-blocking");
 	// Configurer l'adresse et le port du serveur
	memset(&s_address, 0, sizeof(s_address));
    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(atoi(portNumber));
    s_address.sin_addr.s_addr = INADDR_ANY;
	// Lier l'adresse au socket du serveur
	if (bind(s_socket, (struct sockaddr *) &s_address, sizeof(s_address)) < 0) {
	    SERVER_ERR("Error during bind");
		exit(1);
	}
	// Écouter les connexions entrantes
	if (listen(s_socket, 5) < 0)
        SERVER_ERR("Error while listening");
	setCommandList();
	_oper.insert(std::pair<std::string, std::string>("admin", "pwd"));
}

Server::~Server() {
	removeClients();
	close (s_socket);
	std::cout << std::endl << "Server closing, see you next time." << std::endl << std::endl;
}

/**********************************************************************************************************/
/*                                                Méthodes                                                */
/**********************************************************************************************************/

void	Server::removeClients() {
	size_t clientsNb = _clients.size();
	// std::cout << std::endl << "removeClients(void)" << std::endl << std::endl;
	// std::cout << std::endl << "_clients.size(): " << _clients.size() << std::endl << std::endl;
	for (size_t i = 0; i < clientsNb; i++) {
		Client*	tmp = _clients.begin()->second;
		_clients.erase(tmp->getC_socket());
		delete (tmp);
	}	
	// std::cout << std::endl << "_clients.size() 2: " << _clients.size() << std::endl << std::endl;
}

void	Server::acceptClient() {
	int					client_socket;
	struct sockaddr_in	client_address;
	socklen_t			client_len;
	int					yes = 1;
	// Accepter la connexion entrante du client
	client_len = sizeof(client_address);	
    client_socket = accept(getServerSocket(), (struct sockaddr *) &client_address, &client_len);
	if (client_socket == -1)
        SERVER_ERR("Error while accepting connexion");
	if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))== -1)
		SERVER_ERR("setsockopt failed");
	if(fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
		SERVER_ERR("Error while rendering the socket non blocking");
	_clients[client_socket] = new Client(client_socket, client_address, this);
	// Ajouter le socket client à notre tableau de fds
	fds.push_back(pollfd());
	fds.back().fd = client_socket;
	fds.back().events = POLLIN;
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
	if (res == -1)
        SERVER_ERR("Error during receipt");
	// else if (res == 0) {
		// close(fds[client_socket].fd);
		// delete(_clients[client_socket]);
		// this->_clients.erase(client_socket);

		// SERVER_ERR("Client is disconnected");
	// }
	else if (getUser(client_socket) != NULL && res > 0 && buffer_str[buffer_str.size() - 1] != '\n') {
		getUser(client_socket)->setBuffer(getUser(client_socket)->getBuffer().append(buffer_str));
		// std::cout << std::endl << "Receiving End of File, request not completed" << std::endl << std::endl;
	}
	else if (getUser(client_socket) != NULL && res > 0 && buffer_str[buffer_str.size() - 1] == '\n') {
		// std::cout << std::endl << "Receiving Entrée" << std::endl << std::endl;
		getUser(client_socket)->setBuffer(getUser(client_socket)->getBuffer().append(" " + buffer_str));
		getUser(client_socket)->initMsg();	// à deplacer dans le dernier else. On appelle la methode de creation de commande de la classe Client. Le buffer complet est deja stocké dans l'attribut _buffer de l'instance Client. 
		getUser(client_socket)->setBuffer("");
	}
	buffer_str.clear();
}

void Server::init_pollfd_struct() {
	fds.clear();
	fds.push_back(pollfd());	
	fds.back().fd = s_socket;
	fds.back().events = POLLIN;		
	fds.back().revents = 0;

}

void	Server::usePoll() {
	init_pollfd_struct();
	while(!serv_run) { 
		// Préparer le vector de fd pour poll()
		if (poll(fds.data(), fds.size(), timeout) < 0)
		    // SERVER_ERR("Error Poll()");
			break ;
		for (size_t i = 0; i < fds.size(); i++) {
			if (fds[i].revents) {
				// revent == 1 : on a recu une requete de irssi
				if (fds[i].revents & POLLIN) {
					// find the descriptors that returned POLLIN and determine whether it's the listening or the active connection.
					if (i == 0)
						acceptClient();
					else
						// on envoie le socket du dernier client ajouté: fds[i].fd (qu'on a défini dans acceptClient : this->fds.back().fd = client_socket;)
						receiveRequest(fds[i].fd);
				}
				else if (fds[i].revents & POLLRDHUP || fds[i].revents & POLLERR)
	        		SERVER_ERR("Error Poll() in FDS");
			}
		}
	}
}

bool	Server::nickIsUsed(std::string str) const {
	// std::cout << "DEBUG ===> nickIsUsed test"   << std::endl;
	std::map<int, Client*>::const_iterator	it = _clients.begin();
	std::map<int, Client*>::const_iterator	ite = _clients.end();
	for (; it != ite ; it++) {
		// std::cout << "DEBUG ===> existing nicknames: " << (it->second->getNick()) << std::endl;
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

char*								Server::getPortNumber() const { return (portNumber); }
char*								Server::getPassword() const { return (_password); }
int									Server::getTimeout() const { return (timeout); }
int									Server::getServerSocket() const { return (s_socket); }
struct sockaddr_in					Server::getServerAddress() const { return (s_address); }
std::vector<struct pollfd>			Server::getFds() const { return (fds); }
std::map<int, Client*>&				Server::getClients() { return (_clients); }
std::map<std::string, Channel>&		Server::getChannels() { return (_channels); }
std::map<std::string, fct_cmd>&		Server::getCommandList() { return (_commandList); }
std::map<std::string, std::string>&	Server::getOper() { return (_oper); }
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
    for (; it != ite; it++) {
        if (it->second->getNick() == nick)
            return (it->second);
    }
    return (NULL);
}

// void Server::getChannelbyName(std::string chan)
// {
// 	// std::map<std::string, Channel>::iterator it = _channels.begin();
// 	// std::map<std::string, Channel>::iterator ite = _channels.end();
// 	Channel *result;
// 	std::map<std::string, Channel>::const_iterator it = _channels.find(chan);
//     if (it != _channels.end()) {
//         // Channel found, update the result pointer with the address of the associated Channel object
//         *result = &(it->second);
//     } else {
//         // Channel not found, set the result pointer to NULL
//         *result = NULL;
//     }
// }

void	Server::setPortNumber(char* number) { portNumber = number; }

void Server::setCommandList() {
	_commandList.insert(std::make_pair("ADDMOTD", addmotd));
	_commandList.insert(std::make_pair("ADDOMOTD", addomotd));
	_commandList.insert(std::make_pair("CHGHOST", chgname));
	_commandList.insert(std::make_pair("CHGNAME", chgname));
	_commandList.insert(std::make_pair("GLOBOPS", globops));
	_commandList.insert(std::make_pair("JOIN", join));
	_commandList.insert(std::make_pair("KICK", kick));
	_commandList.insert(std::make_pair("kill", ft_kill));
	_commandList.insert(std::make_pair("LIST", list));
	_commandList.insert(std::make_pair("MODE", mode));
	_commandList.insert(std::make_pair("motd", motd));
	_commandList.insert(std::make_pair("NAMES", names));
	_commandList.insert(std::make_pair("NICK", nick));
	_commandList.insert(std::make_pair("OPER", oper));
	_commandList.insert(std::make_pair("OPERMOTD", opermotd));
	_commandList.insert(std::make_pair("PART", part));
	_commandList.insert(std::make_pair("PASS", pass));
	_commandList.insert(std::make_pair("PING", ping));
	_commandList.insert(std::make_pair("PRIVMSG", privmsg));
	_commandList.insert(std::make_pair("QUIT", quit));
	_commandList.insert(std::make_pair("USER", user));
	_commandList.insert(std::make_pair("WALLOPS", wallops));
	_commandList.insert(std::make_pair("WHOIS", whoIs));
}
