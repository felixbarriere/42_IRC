#ifndef	UTILS_HPP
#define UTILS_HPP

#define BUFFER_SIZE	512 // max size?

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <vector>
#include <map>
#include <signal.h>
#include <fcntl.h>
#include <netdb.h>
#include <ctime>
#include "class/server.hpp"
#include "class/client.hpp"
#include "class/message.hpp"


//****************Configs*************
#define NAME "irc" 
//max 63 ch-s
#define MOTD "hola chicos! "
#define VERSION "1.0"
#define MAX_BACKLOGS 5
//the maximum value is system-dependent (usually 5)
#define MAX_USERS 20
#define OPER_USER "admin"
#define OPER_PASSWORD "pwd"
#define PING 30
#define TIMEOUT 1000

extern int serv_run;

void						next_steps(Server	*server);
void						ft_handler(int smth);
std::vector<std::string>	ft_split(const std::string &str, const std::string &sep);
void showConfig(void);
int							checkCommand(std::string	str);
std::string					ft_trim(std::string	str, char toTrim);


#endif