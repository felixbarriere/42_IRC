/* A utiliser:

poll():    
Surveille plusieurs sockets dans votre chat IRC en C++. 
La fonction poll() prend en entrée un tableau de structures pollfd,
chacune correspondant à un socket à surveiller, et retourne 
lorsqu'un socket est prêt à lire ou à écrire.

int poll(struct pollfd *fds, nfds_t nfds, int délai);

struct pollfd {
    int   fd;         => Descripteur de fichier 
    short events;     => Événements attendus    
    short revents;    => Événements détectés    
};
--------------------------------------------------------------

socket() : 
Utiliser les sockets pour créer une connexion réseau entre plusieurs ordinateurs.

The socket() function shall create an unbound socket in a 
communications domain, and return a file descriptor that can be used in 
later function calls that operate on sockets.
			
int socket(int domain, int type, int protocol);

INADDR_ANY binds the socket to all available interfaces.
--------------------------------------------------------------

struct sockaddr_in, struct in_addr:
Structures for handling internet addresses

--------------------------------------------------------------

htons():
The htons() function converts the unsigned short integer hostshort
from host byte order to network byte order.

--------------------------------------------------------------


*/

#include "srcs/utils.hpp"


int	main (int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Error " << std::endl << "Syntax: ./IRC PORT PASSWORD" << std::endl ;
		return (1);
	}

	std::cout << "DEBUG ===> Test host Main:" << av[1] << std::endl << std::endl;

	Server	server(av[1], av[2]);
	

	next_steps(server);


	return (0);
}
