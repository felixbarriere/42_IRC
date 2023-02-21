// #include "server.hpp"
#include "utils.hpp"




void	next_steps(Server	*server)
{
	int client_socket;
	struct sockaddr_in client_address;
	socklen_t client_len;

	// use_poll( server);	==> redondant avec la methode server->usePoll()

	std::cout << "DEBUG ===> AFTER POLL" << std::endl << std::endl;


	/****** PLACER dans la methode server->acceptClient ******/

	// Accepter la connexion entrante du client	
	client_len = sizeof(client_address);	
	// comment récupère-t-on l'addresse du client?
    client_socket = accept(server->getServerSocket(), (struct sockaddr *) &client_address, &client_len);  //passe de 5 connexions possibles à 4
    
	std::cout << "DEBUG ===>  AFTER ACCEPT: client_socket = " << client_socket << std::endl << std::endl;
	

	if (client_socket < 0)
        SERVER_ERR("Error while accepting connexion");
	else
		std::cout << "ACCEPT OK, got connexion from " << inet_ntoa(client_address.sin_addr) 
		<< " port " << ntohs(client_address.sin_port) << std::endl;

	// apres accept(), envoyer client_socket pour l'instanciation de la classe Client.

	// instancier la classe Client;
}


// void	use_poll(Server *server)
// {
// 	// int poll(struct pollfd *fds, nfds_t nfds, int délai);

// 	// ------------ premiere solution: marche comme ca (hors de la classe) mais oblige a parametrer fds dans la fonction au lieu du constructeur

// 	std::vector<struct pollfd> 	fds_test;

// 	fds_test.clear();
// 	fds_test.push_back(pollfd());			// pas trop compris, on instancie la structure pollfd pour avoir un premier élément dans le vecteur?
// 	fds_test.back().fd = server->getServerSocket();
//     fds_test.back().events = POLLIN;		// données en attente de lecture.
//     fds_test.back().revents = 0;

// 	std::cout << "DEBUG ===> BEFORE POLL() 1" << std::endl << std::endl;
// 	std::cout << "DEBUG ===> fds_test.data():" << fds_test.data() << std::endl << std::endl;
// 	std::cout << "DEBUG ===> &server.getFds()[0]:" << &server->getFds()[0] << std::endl << std::endl;

// 	if (poll(fds_test.data(), fds_test.size(), server->getTimeout()) < 0)
//         SERVER_ERR("Error Poll()");


// 	std::cout << "DEBUG ===> server.getServerSocket():" << server->getServerSocket() << std::endl << std::endl;

// }