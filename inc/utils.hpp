#ifndef	UTILS_HPP
# define UTILS_HPP

/*** MACRO ***/

# define BUFFER_SIZE	512 // max size?

/*** LIBRARY ***/

# include <arpa/inet.h>
# include <cstring>
# include <errno.h>
# include <fcntl.h>
# include <fstream>
# include <iostream>
# include <map>
# include <netinet/in.h>
# include <poll.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
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
