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

!!!Some server software allows you to specify multiple channels or nicknames by separating them with commas (e.g. KICK #v3 tom,jerry).
However, this is not universally supported so stick to one channel and nick per kick command.

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

    std::vector<std::string> channels = ft_split(client->getMessage()->getParams()[0], ",");
	std::vector<std::string> users = ft_split(client->getMessage()->getParams()[1], ",");

    // for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
	// {
    //     if (!client->getChannel()does not exist)
    //             client->sendMsg(ERR_NOSUCHCHANNEL + client->getNick() + " " + *it + " :No such channel");
    //     else if(checkMode(client) == false)
    //             client->sendMsg(ERR_CHANOPRIVSNEEDED + client->getNick() + " " + *it  + " :You're not channel operator");
    //     else
    //         {
    //             for (std::vector<std::string>::iterator it2 = users.begin(); it2 != users.end(); ++it2)
    //             {
    //                 if (//does not exist)
    //                     client->sendMsg(ERR_USERNOTINCHANNEL + client->getNick() + *it + " " + *it2  + " :They aren't on that channel");
    //                 else
    //                 {
    //                     std::string str =  "KICK " + *it + " " + *it2 + " :" + client->getMessage()->getParams()[2]);
    //                     broadcast a message to the concerned user
    //                     send message to all users of the channel
    //                     client->getChannel()->broadcast(server->getUserbyNick(client->getMessage()->getParams()[1], str)
    //                     client->getChannel().removeMember(//what client?);
    //                 }
    //             }
	//         }
    // }
}