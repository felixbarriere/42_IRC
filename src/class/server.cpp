// #include "server.hpp"
#include "utils.hpp"

Server::Server() {}

Server::Server(char* portNumberMain, char *password) : portNumber(portNumberMain), password(password), timeout(20000)
{
	// int timeout = -1;

	// Initialiser le socket du serveur (a mettre dans la class server)
	this->s_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->s_socket < 0)
		SERVER_ERR("Error during socket creation.");
	else
		std::cout << "SOCKET CREATION OK" << std::endl;

 	// Configurer l'adresse et le port du serveur	(a mettre dans la class server)
	memset(&this->s_address, 0, sizeof(this->s_address));
    this->s_address.sin_family = AF_INET;
    this->s_address.sin_port = htons(atoi(this->portNumber));   // convert short integer value for port must be converted into network byte order
    this->s_address.sin_addr.s_addr = INADDR_ANY;

	// Lier l'adresse au socket du serveur
	if (bind(this->s_socket, (struct sockaddr *) &this->s_address, sizeof(this->s_address)) < 0)
        SERVER_ERR("Error during bind.");   // try above 1024: the first 1024 ports are 'special' and usually need super user privileges to use them
	else
		std::cout << "BIND OK" << std::endl;

	// Écouter les connexions entrantes
	if (listen(this->s_socket, 5) < 0)				//  5: backlog définit une longueur maximale jusqu'à laquelle la file des connexions en attente pour sockfd peut croître.
        SERVER_ERR("Error while listening.");
	else 
		std::cout << "LISTEN OK" << std::endl;


	

}

Server::~Server() 
{
	std::cout << "DEBUG ===> Destructor, closing server socket" << std::endl << std::endl;

	close(this->s_socket);	
}

void	Server::usePoll(void)
{
	// https://www.ibm.com/docs/en/i/7.3?topic=designs-using-poll-instead-select
	// int poll(struct pollfd *fds, nfds_t nfds, int délai);

	std::cout << "DEBUG ===> BEFORE POLL()" << std::endl;
	std::cout << "DEBUG ===> this->getFds().data():" << this->getFds().data() << std::endl;
	std::cout << "DEBUG ===> &this->getFds().front():" << &this->getFds().front() << std::endl;
	std::cout << "DEBUG ===> &this->fds[0]:" << &this->fds[0] << std::endl << std::endl;

	while(1)
	{ 


		// Préparer le vector de fd pour poll()
		this->fds.clear();
		this->fds.push_back(pollfd());			// pas trop compris, on instancie la structure pollfd pour avoir un premier élément dans le vecteur?
		this->fds.back().fd = this->s_socket;
	    this->fds.back().events = POLLIN;		// données en attente de lecture.
	    this->fds.back().revents = 0;

		if (poll(fds.data(), this->fds.size(), this->timeout) < 0)	// ou &this->fds[0], mais fds.data() permet de boucler par la suite
	        SERVER_ERR("Error Poll()");

		for (size_t i; i < this->fds.size(); i++)
		{
			if (this->fds[i].revents != 0) //revent == 1 : on a recu une connexion de irssi
			{

				if (this->fds[i].revents == POLLIN)	// find the descriptors that returned POLLIN and determine whether it's the listening or the active connection.
				{
					if (i == 0)
					{
						std::cout << "DEBUG ===> ACCEPT New Client" << std::endl;
						// creer une methode acceptClient avec accept()
					}
					else
					{
						std::cout << "DEBUG ===> Receive request" << std::endl;
						// creer une methode receiveRequest avec recv()
					}
				}
			}
		}

		std::cout << "DEBUG ===> Server running (sleep: 3 seconds)" << std::endl;
		sleep(3);
	}
	
	// If revents is not POLLIN, it's an unexpected result, log and end the server.          
}

char*						Server::getPortNumber(void) {	return (this->portNumber);	}
char*						Server::getPassword(void) {	return (this->password);	}
int							Server::getTimeout(void) {	return (this->timeout); }
int							Server::getServerSocket(void) {	return (this->s_socket);	}
struct sockaddr_in			Server::getServerAddress(void) {	return (this->s_address);}
std::vector<struct pollfd>	Server::getFds(void) {	return (this->fds);	}




void	Server::setPortNumber(char * portNumber) {	this->portNumber = portNumber;	}
