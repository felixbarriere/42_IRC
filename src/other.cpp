// #include "server.hpp"
#include "utils.hpp"

void	use_poll(Server server)
{
	// ------------ premiere solution: marche comme ca (hors de la classe) mais oblige a parametrer fds dans la fonction au lieu du constructeur

	std::vector<struct pollfd> 	fds_test;

	fds_test.clear();
	fds_test.push_back(pollfd());			// pas trop compris, on instancie la structure pollfd pour avoir un premier élément dans le vecteur?
	fds_test.back().fd = server.getServerSocket();
    fds_test.back().events = POLLIN;		// données en attente de lecture.
    fds_test.back().revents = 0;

	std::cout << "DEBUG ===> BEFORE POLL()" << std::endl << std::endl;

	if (poll(fds_test.data(), fds_test.size(), server.getTimeout()) < 0)
        SERVER_ERR("Error Poll()");






	//  ------------ deuxieme solution marche surement juste si on la met dans une methode de la classe Server. A tester.

	// PROTOTYPE: int poll(struct pollfd *fds, nfds_t nfds, int délai);

	// if (poll(&server.getFds().front(), server.getFds().size(), server.getTimeout()) < 0)
    //     SERVER_ERR("Error Poll()");
		
	// terminate called after throwing an instance of 'std::bad_array_new_length'
	// uninitialized value mais server.fds est bien initialisée

	std::cout << "DEBUG ===> AFTER POLL()" << std::endl << std::endl;

}


void	next_steps(Server	server)
{
	int client_socket;
	struct sockaddr_in client_address;
	socklen_t client_len;

	std::cout << "DEBUG ===> TEST NEXT STEPS" << std::endl << std::endl;

	use_poll( server);


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