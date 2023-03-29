#ifndef	UTILS_HPP
# define UTILS_HPP

/*** MACRO ***/

# define BUFFER_SIZE 512

//*****  Configs  *****
# define NAME "irc" 
//max 63 ch-s
# define VERSION "1.0"
# define MAX_BACKLOGS 5
//the maximum value is system-dependent (usually 5)
# define MAX_USERS 5
# define OPER_USER "admin"
# define OPER_PASSWORD "admin_pwd"
# define PING 30
# define TIMEOUT 5000

/*** REPLY CODE ***/

# define RPL_WELCOME			"001 "
# define RPL_YOURHOST			"002 "
# define RPL_CREATED			"003 "
# define RPL_MYINFO				"004 "
# define RPL_LIST				"322 "
# define RPL_LISTEND			"323 "
# define RPL_MOTD				"372 "
# define RPL_MOTDSTART			"375 "
# define RPL_ENDOFMOTD			"376 "


/*** COMMAND ERRORS ***/




# define RPL_UMODEIS			"221 "
# define RPL_YOUREOPER          "381 "
# define RPL_NAMREPLY          	"353 "
# define RPL_ENDOFNAMES 		"366 "


# define ERR_NOSUCHNICK			"401 "
# define ERR_NOSUCHCHANNEL      "403 "
# define ERR_NOORIGIN			"409 "
# define ERR_NORECIPIENT		"411 "
# define ERR_NOTEXTTOSEND		"412 "
# define ERR_NOMOTD				"422 "
# define ERR_NONICKNAMEGIVEN	"431 "
# define ERR_ERRONEUSNICKNAME	"432 "
# define ERR_NICKNAMEINUSE		"433 "
# define ERR_USERNOTINCHANNEL   "441 "
# define ERR_NOTONCHANNEL		"442 "
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
# include <string>
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

void						ft_handler(int);
std::vector<std::string>	ft_split(const std::string&, const std::string&);
void 						showConfig();
bool						checkCommand(std::string);
std::string					ft_trim(std::string, char);
bool                        checkMode(Client*);
int							checkPort(char*);

class Server;
void	addmotd(Server*, Client*);
void	addomotd(Server*, Client*);
void	chghost(Server*, Client*);
void	chgname(Server*, Client*);
void	globops(Server*, Client*);
void	join(Server*, Client*);
void	kick(Server*, Client*);
void	ft_kill(Server*, Client*);
void	list(Server*, Client*);
void	mode(Server*, Client*);
void	motd(Server*, Client*);
void	msg(Server*, Client*);
void	names(Server*, Client*);
void	nick(Server*, Client*);
void	notice(Server*, Client*);
void	oper(Server*, Client*);
void	part(Server*, Client*);
void	pass(Server*, Client*);
void	ping(Server*, Client*);
void	privmsg(Server*, Client*);
void	quit(Server*, Client*);
void	user(Server*, Client*);
void	wallops(Server*, Client*);
void	whoIs(Server*, Client*);

#endif
