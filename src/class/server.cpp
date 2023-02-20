#include "utils.hpp"

server::server() 
{
	std::cout << "Uninitialised server" << std::endl;
}

server::server(char* portNumberMain)
{
	int server_socket, client_socket;
	struct sockaddr_in server_address;//usually named "hint"
	struct sockaddr client_address;
	struct pollfd fds[2];
	socklen_t client_len;
	this->portNumber = portNumberMain;
	// int nfds = 2;
	// int timeout = -1;

	// Initialiser le socket du serveur (a mettre dans la class server)
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
		SERVER_ERR("Error during socket creation.");

 	// Configurer l'adresse et le port du serveur	(a mettre dans la class server)
	memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(this->portNumber));//host_to_network_short
    //inet_pton(AF_INET, "0.0.0.0", &server_address.sin_addr);
	server_address.sin_addr.s_addr = INADDR_ANY;

	std::cout << "Test host:" << this->portNumber << std::endl;
	std::cout << "Test host (network byte order):" << server_address.sin_port << std::endl;


	// Lier l'adresse au socket du serveur
	if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        SERVER_ERR("Error during bind.");   // try above 1024: the first 1024 ports are 'special'
		//and usually need super user privileges to use them
	else
		std::cout << "BIND OK" << std::endl;

	// Écouter les connexions entrantes SOMAXCONN=max_connection
	if (listen(server_socket, 5) < 0)
        SERVER_ERR("Error while listening.");

	// Accepter la connexion entrante du client	
	client_len = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_len);
    if (client_socket < 0)
        SERVER_ERR("Error while accepting connexion.");


    // Configurer les sockets pour la surveillance avec poll
    memset(fds, 0, sizeof(fds));
    fds[0].fd = server_socket;
    fds[0].events = POLLIN;
    fds[1].fd = client_socket;

}

server::~server() {
	//close(server_address);
}

void	server::setPortNumber(char * portNumber) {	this->portNumber = portNumber;	}
