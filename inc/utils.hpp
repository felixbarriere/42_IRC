#ifndef	UTILS_HPP
#define UTILS_HPP

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


#include "class/server.hpp"


void	next_steps(Server	server);


#endif