// #include "server.hpp"
#include "utils.hpp"

/***************************************************************************************************************************/
/*                                                Constructors / Destructor                                                */
/***************************************************************************************************************************/

Server::Server() {}

Server::Server(char* portNumberMain, char *password) : portNumber(portNumberMain), _password(password), timeout(20000)
{
	showConfig();
	int yes = 1;

	// Initialiser le socket du serveur (a mettre dans la class server)
	this->s_socket = socket(AF_INET, SOCK_STREAM, 0);//AF_INET - IPv4
    if (this->s_socket < 0)
		SERVER_ERR("Error during socket creation");
	else
		std::cout << "SOCKET CREATION OK" << std::endl;

	//rendre le socket non-bloquant
	if (setsockopt(s_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))== -1)
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
	else
		std::cout << "BIND OK" << std::endl;

	// Écouter les connexions entrantes
	if (listen(this->s_socket, 5) < 0) //SOMAXCONN (4096 on school machine)   5: backlog définit une longueur maximale jusqu'à laquelle la file des connexions en attente pour sockfd peut croître.
        SERVER_ERR("Error while listening");
	else 
		std::cout << "LISTEN OK" << std::endl;
}

Server::~Server()
{
	std::cout << "DEBUG ===> Destructor, closing server socket" << std::endl << std::endl;

	close(this->s_socket);
}

/**********************************************************************************************************/
/*                                                Méthodes                                                */
/**********************************************************************************************************/

void	Server::acceptClient(void)
{
	int client_socket;
	struct sockaddr_in client_address;
	socklen_t client_len;
	int yes = 1;

	// Accepter la connexion entrante du client	
	client_len = sizeof(client_address);	
    client_socket = accept(this->getServerSocket(), (struct sockaddr *) &client_address, &client_len);  //passe de 5 connexions possibles à 4
    
	std::cout << "DEBUG ===>  AFTER ACCEPT: client_socket = " << client_socket << std::endl << std::endl;

	if (client_socket == -1)
        SERVER_ERR("Error while accepting connexion");
	std::cout << "ACCEPT OK, got connexion from " << inet_ntoa(client_address.sin_addr)
		<< " port " << ntohs(client_address.sin_port) << std::endl << std::endl;
	if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))== -1)
		SERVER_ERR("setsockopt failed");
	if(fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
		SERVER_ERR("Error while rendering the socket non blocking");

	// instancier la classe Client
	// utiliser new: "Client *new_client" est simplement la déclaration d'un pointeur de type Client, mais il ne crée pas d'objet Client ni n'alloue de mémoire pour un tel objet ==> comportement indéfini.
	this->clients[client_socket] = new Client(client_socket, client_address);

	// On ajoute le socket client à notre tableau de fds
	this->fds.push_back(pollfd());	// fds argument, which is an array of structures of the following form: 
	this->fds.back().fd = client_socket;
	this->fds.back().events = POLLIN;		// données en attente de lecture.
	this->fds.back().revents = POLLIN;
}

void	Server::receiveRequest(int	client_socket)
{
	char 	buffer[BUFFER_SIZE + 1];
	int		res;

	std::cout << "DEBUG ===> Receive request" << std::endl << std::endl;

	memset(buffer, 0, BUFFER_SIZE + 1);

	// int recv(int client_socket, void* buffer, size_t len, int flags);
	res = recv(client_socket , buffer, BUFFER_SIZE, 0);

	std::cout << "result of recv() = " << res << std::endl;
	std::string buffer_str(buffer);

	if (res == -1)
        SERVER_ERR("Error during receipt");
	else if (res == 0)
	{
		delete(this->clients[client_socket]);
		std::cout << "Client is disconnected " << res << std::endl;
		// SERVER_ERR("Client is disconnected");
	}
	else if (res > 0 && (buffer_str.rfind("\n\r")) != (buffer_str.size() - 2))
	{
		std::cout << "Command incomplete: on append() le buffer recu par bouts" <<std::endl;
		this->getUser(client_socket)->setBuffer(this->getUser(client_socket)->getBuffer().append(buffer_str));	// strcat() works only for char *
		this->getUser(client_socket)->createCommandList();	// à deplacer dans le dernier else. On appelle la methode de creation de commande de la classe Client. Le buffer complet est deja stocké dans l'attribut _buffer de l'instance Client. 
	}
	else 
	{
		std::cout << "DEBUG ===> recv > 0 : MESSAGE FROM CLIENT"  << std::endl << std::endl;
	}
	
	buffer_str.clear();
	std::cout << "buffer_size : " << buffer_str.size() <<std::endl;
}

void Server::init_pollfd_struct(void)
{
	this->fds.clear();
	this->fds.push_back(pollfd());	
	this->fds.back().fd = this->s_socket;
	this->fds.back().events = POLLIN;		
	this->fds.back().revents = 0;

	//la 2eme partie de la fct est censee d'initialiser le reste des clients
}

void	Server::usePoll(void)
{
	init_pollfd_struct();

	while(!serv_run)
	{ 
		// Préparer le vector de fd pour poll()
		if (poll(fds.data(), this->fds.size(), this->timeout) < 0)	// ou &this->fds[0], mais fds.data() permet de boucler par la suite
	        SERVER_ERR("Error Poll()");

		for (size_t i = 0; i < this->fds.size(); i++)
		{
			if (this->fds[i].revents != 0) //revent == 1 : on a recu une requete de irssi
			{
				if (this->fds[i].revents & POLLIN)	// find the descriptors that returned POLLIN and determine whether it's the listening or the active connection.
				{
					if (i == 0)
					{
						this->acceptClient();
					}
					else
					{
						this->receiveRequest(fds[i].fd);  //	on envoie le socket du dernier client ajouté: fds[i].fd (qu'on a défini dans acceptClient : this->fds.back().fd = client_socket;)
					}
				}
				else if (this->fds[i].revents & POLLRDHUP || this->fds[i].revents & POLLERR)
				{
	        		SERVER_ERR("Error Poll() in FDS");
				}
			}
		}
		std::cout << std::endl << " Server running (sleep: 1)" << std::endl;
		sleep(5);
	}
}


/*******************************************************************************************************************/
/*                                                Getters / Setters                                                */
/*******************************************************************************************************************/

char*						Server::getPortNumber(void) {	return (this->portNumber);	}
char*						Server::getPassword(void) {	return (this->_password);	}
int							Server::getTimeout(void) {	return (this->timeout); }
int							Server::getServerSocket(void) {	return (this->s_socket);	}
struct sockaddr_in			Server::getServerAddress(void) {	return (this->s_address);}
std::vector<struct pollfd>	Server::getFds(void) {	return (this->fds);	}
std::map<int, Client*>		Server::getClients(void) {	return (this->clients);	}

Client*						Server::getUser(int fd)
{
	std::map<int, Client*>::const_iterator	ret;
	ret = this->clients.find(fd);
	if (ret == this->clients.end())
		return NULL;
	return ret->second;

}

void	Server::setPortNumber(char * portNumber) {	this->portNumber = portNumber;	}
