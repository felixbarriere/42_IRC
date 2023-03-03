#ifndef	UTILS_HPP
#define UTILS_HPP

/*** MACRO ***/

# define BUFFER_SIZE	512 // max size?

//*****  Configs  *****
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

/*** LIBRARY ***/

# include <arpa/inet.h>
# include <cstring>
# include <ctime>
# include <errno.h>
# include <fcntl.h>
# include <fstream>
# include <iostream>
# include <map>
# include <netdb.h>
# include <netinet/in.h>
# include <poll.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>
# include <utility>
# include <vector>

/*** CLASS ***/

# include "class/server.hpp"
# include "class/client.hpp"
# include "class/message.hpp"
# include "class/channel.hpp"

/*** GLOBAL VARIABLE ***/

extern int serv_run;

/*** PROTOTYPE ***/

void						ft_handler(int smth);
std::vector<std::string>	ft_split(const std::string &str, const std::string &sep);
void 						showConfig(void);
int							checkCommand(std::string	str);
std::string					ft_trim(std::string	str, char toTrim);
void						addmotd(Client *client, const std::string text);
void						addomotd(Client *client, const std::string text);
void						chgname(Client *changer, Client *changee, const std::string name);
void						join(Server *server, Client *client, const std::string name);
void						list(Client *client, const Server *server);
void						motd(Client *client);
void						names(Channel *channel);
void						nick(Client *client, const std::string nick);
void						user(Client *client, const std::string user);

#endif
