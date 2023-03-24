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

std::ostream& operator<<(std::ostream& out, const std::vector<std::string>& vec) {
    out << "[ ";
    for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        out << *it << " ";
    out << "]";
    return (out);
}

void	kick(Server* server, Client* client) {
    if (!server)
        return ;
    // std::cout << "DEBUG ===> KICK called"  << std::endl << std::endl;
    if (client->getMessage()->getParams().size() < 3)
        client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + ":Not enough parameters");
    std::vector<std::string> channels = ft_split(client->getMessage()->getParams()[0], ",");
	std::vector<std::string> users = ft_split(client->getMessage()->getParams()[1], ",");
    // std::cout << " channels vector: " << channels << std::endl;
    // std::cout << " users vector: " << users << std::endl;
    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if (client->getChannelName() != *it)
                client->sendMsg(ERR_NOSUCHCHANNEL + client->getNick() + " " + *it + " :No such channel");
        else if(!checkMode(client))
                client->sendMsg(ERR_CHANOPRIVSNEEDED + client->getNick() + " " + *it  + " :You're not channel operator");
        else {
            // std::cout << "check existant users and kick then " << std::endl;
            for (std::vector<std::string>::iterator it2 = users.begin(); it2 != users.end(); ++it2) {
                if (client->getChannel()->getMemberName(*it2) != *it2)
                    client->sendMsg(ERR_USERNOTINCHANNEL + client->getNick() + *it + " " + *it2  + " :They aren't on that channel");
                else {
                    std::string str =  "KICK " + *it + " " + *it2 + " :" + client->getMessage()->getParams()[2];
                    std::cout << str << std::endl;  
                    // broadcast a message to the concerned user
                    // send message to all users of the channel
                    // client->getChannel()->broadcast(client, str);
                    // client->getChannel()->removeMember(server->getUserbyNick(*it2));
                }
            }
        }
    }
}