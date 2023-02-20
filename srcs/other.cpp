// #include "server.hpp"
#include "utils.hpp"


// void	use_poll(struct pollfd fds, Server	server)
// {
//     // Configurer les sockets pour la surveillance avec poll (doit etre avant la fonction accept(), determine si on accepte ou pas)
//     memset(fds, 0, sizeof(fds));
//     fds[0].fd = server.s_socket;
//     fds[0].events = POLLIN;		// données en attente de lecture.
//     fds[0].revents = 0;
//     // fds[1].fd = client_socket;
// }



void	next_steps(Server	server)
{
	int client_socket;
	struct sockaddr_in client_address;
	// struct pollfd fds[2];	// changer en vector pour pouvoir accepter toutes les sizes
	socklen_t client_len;

	std::cout << "TEST NEXT STEPS" << std::endl;

	// use_poll(fds, server);


	// Accepter la connexion entrante du client	
	client_len = sizeof(client_address);	
	// comment récupère-t-on l'addresse du client?
    client_socket = accept(server.s_socket, (struct sockaddr *) &client_address, &client_len);  //passe de 5 connexions possibles à 4
    if (client_socket < 0)
        SERVER_ERR("Error while accepting connexion.");
	else
		std::cout << "ACCEPT OK, got connexion from " << inet_ntoa(client_address.sin_addr) 
		<< " port " << ntohs(client_address.sin_port) << std::endl;

	// apres accept(), envoyer client_socket pour l'instanciation de la classe Client.

	// instancier la classe Client;
}