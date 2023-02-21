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

https://www.ibm.com/docs/en/i/7.3?topic=designs-using-poll-instead-select

--------------------------------------------------------------

socket() : 
Utiliser les sockets pour créer une connexion réseau entre plusieurs ordinateurs.

The socket() function shall create an unbound socket in a 
communications domain, and return a file descriptor that can be used in 
later function calls that operate on sockets. => On success, a file descriptor
for the new socket is returned.  On error, -1 is returned, and errno is set to indicate the error.
			
int socket(int domain, int type, int protocol);

INADDR_ANY binds the socket to all available interfaces.
--------------------------------------------------------------

struct sockaddr_in, struct in_addr:
Structures for handling internet addresses

--------------------------------------------------------------

htons():
The htons() function converts the unsigned short integer hostshort
from host byte order to network byte order.

--------------------------------------------------------------*/

#include "../inc/utils.hpp"

int  serv_run = 0;

void ft_handler(int smth)
{
	(void)smth;
	serv_run = 1;
}

int	main (int ac, char **av)
{
	signal(SIGINT, ft_handler);
	if (ac != 3)
	{
		std::cerr << "Error " << std::endl << "Syntax: ./IRC PORT PASSWORD" << std::endl ;
		return (1);
	}

	Server	server(av[1], av[2]);
	
	server.usePoll();


	next_steps(&server);

	return (0);
}
