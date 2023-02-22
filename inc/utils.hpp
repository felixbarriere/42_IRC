#ifndef	UTILS_HPP
#define UTILS_HPP

#define BUFFER_SIZE	512 // max size?

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <poll.h>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <vector>
#include <map>
#include <signal.h>

#include "class/server.hpp"
#include "class/client.hpp"

extern int serv_run;

void	next_steps(Server	*server);
void ft_handler(int smth);


#endif