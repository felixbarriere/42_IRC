// #include "server.hpp"
#include "utils.hpp"

// void	next_steps(Server	*server)
// {
// 	int client_socket;
// 	struct sockaddr_in client_address;
// 	socklen_t client_len;

// 	// use_poll( server);	==> redondant avec la methode server->usePoll()

// 	std::cout << "DEBUG ===> AFTER POLL" << std::endl << std::endl;


// 	/****** PLACER dans la methode server->acceptClient ******/

// 	// Accepter la connexion entrante du client	
// 	client_len = sizeof(client_address);	
// 	// comment récupère-t-on l'addresse du client?
//     client_socket = accept(server->getServerSocket(), (struct sockaddr *) &client_address, &client_len);  //passe de 5 connexions possibles à 4
    
// 	std::cout << "DEBUG ===>  AFTER ACCEPT: client_socket = " << client_socket << std::endl << std::endl;
	

// 	if (client_socket < 0)
//         SERVER_ERR("Error while accepting connexion");
// 	else
// 		std::cout << "ACCEPT OK, got connexion from " << inet_ntoa(client_address.sin_addr) 
// 		<< " port " << ntohs(client_address.sin_port) << std::endl;

// 	// apres accept(), envoyer client_socket pour l'instanciation de la classe Client.


