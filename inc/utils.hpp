#ifndef	UTILS_HPP
# define UTILS_HPP

/*** MACRO ***/

# define BUFFER_SIZE 512 // max size?

//*****  Configs  *****
# define NAME "irc" 
//max 63 ch-s
# define VERSION "1.0"
# define MAX_BACKLOGS 5
//the maximum value is system-dependent (usually 5)
# define MAX_USERS 20
# define OPER_USER "admin"
# define OPER_PASSWORD "admin_pwd"
# define PING 30
# define TIMEOUT 5000

/*** REPLY CODE ***/

# define RPL_WELCOME "001 "
# define RPL_YOURHOST "002 "
# define RPL_CREATED "003 "
# define RPL_MYINFO "004 "

/*** COMMAND ERRORS ***/

# define RPL_UMODEIS			"221 "
# define RPL_YOUREOPER          "381 "
# define ERR_NOSUCHNICK			"401 "
# define ERR_NOSUCHCHANNEL      "403 "
# define ERR_NOORIGIN			"409 "
# define ERR_NONICKNAMEGIVEN	"431 "
# define ERR_ERRONEUSNICKNAME	"432 "
# define ERR_NICKNAMEINUSE		"433 "
# define ERR_USERNOTINCHANNEL   "441 "
# define ERR_NEEDMOREPARAMS 	"461 "
# define ERR_ALREADYREGISTERED	"462 "
# define ERR_PASSWDMISMATCH		"464 "
# define ERR_NOPRIVILEGES       "481 "
# define ERR_CHANOPRIVSNEEDED   "482 "
# define ERR_UMODEUNKNOWNFLAG	"501 "
# define ERR_USERSDONTMATCH		"502 "


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
# include <sstream>
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
bool						checkCommand(std::string str);
std::string					ft_trim(std::string	str, char toTrim);
bool                        checkMode(Client *client);

class Server;
void	addmotd(Server *server, Client *client);
void	addomotd(Server *server, Client *client);
void	chghost(Server *server, Client *client);
void	chgname(Server *server, Client *client);
void	globops(Server *server, Client *client);
void	kick(Server *server, Client *client);
void	ft_kill(Server *server, Client *client);
void	join(Server *server, Client *client);
void	list(Server *server, Client *client);
void	mode(Server *server, Client *client);
void	motd(Server *server, Client *client);
void	opermotd(Server *server, Client *client);
void	names(Server *server, Client *client);
void	nick(Server *server, Client *client);
void	oper(Server *server, Client *client);
void	ping(Server *server, Client *client);
void	part(Server *server, Client *client);
void	pass(Server *server, Client *client);
void	privmsg(Server *server, Client *client);
void	user(Server *server, Client *client);
void	wallops(Server *server, Client *client);
void	whoIs(Server *server, Client *client);
void	quit(Server *server, Client *client);

#endif
