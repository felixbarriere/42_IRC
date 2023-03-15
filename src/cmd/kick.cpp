#include "../../inc/utils.hpp"

/*KICK message

      Command: KICK
   Parameters: <channel> <user> *( "," <user> ) [<comment>]
   
The KICK command can be used to request the forced removal of a user from a channel.
It causes the <user> to be removed from the <channel> by force. 
If no comment is given, the server SHOULD use a default message instead.
The server MUST NOT send KICK messages with multiple users to clients. 
This is necessary to maintain backward compatibility with existing client software.
Servers MAY limit the number of target users per KICK command via the TARGMAX parameter of RPL_ISUPPORT,
and silently drop targets if the number of targets exceeds the limit.

Numeric Replies:
ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_CHANOPRIVSNEEDED (482)
ERR_USERNOTINCHANNEL (441)
ERR_NOTONCHANNEL (442)*/

void	kick(Server *server, Client *client)
{
    if (server == NULL)
        return ;
    
    if (client->getMessage()->getParams().size() == 0)
        client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + ":Not enough parameters");

}