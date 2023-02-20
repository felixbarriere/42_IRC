// #include "server.hpp"
#include "utils.hpp"

// void	use_poll(fds, server)
// {
	
// 	int poll(struct pollfd *fds, nfds_t nfds, int délai);

// }


void	next_steps(Server	server)
{
	int client_socket;
	struct sockaddr_in client_address;
	socklen_t client_len;

	std::cout << "DEBUG ===> TEST NEXT STEPS" << std::endl << std::endl;

	// use_poll(fds, server);


	// Accepter la connexion entrante du client	
	client_len = sizeof(client_address);	
	// comment récupère-t-on l'addresse du client?
    client_socket = accept(server.getServerSocket(), (struct sockaddr *) &client_address, &client_len);  //passe de 5 connexions possibles à 4
    if (client_socket < 0)
        SERVER_ERR("Error while accepting connexion");
	else
		std::cout << "ACCEPT OK, got connexion from " << inet_ntoa(client_address.sin_addr) 
		<< " port " << ntohs(client_address.sin_port) << std::endl;

	// apres accept(), envoyer client_socket pour l'instanciation de la classe Client.

	// instancier la classe Client;
}