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

void    kick(Server* server, Client* client) {
    if (!server)
        return ;

    std::cout << "DEBUG ===> KICK called"  << std::endl << std::endl;
        std::cout << "The whole msg is : " << client->getMessage()->getMessage() << std::endl;

    if (client->getMessage()->getParams().size() < 3) {
        client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + ":Not enough parameters");}

        std::cout << "All the parameters: " << std::endl;
        std::cout << "param 0 " << client->getMessage()->getParams()[0] << std::endl;
        std::cout << "param 1 " << client->getMessage()->getParams()[1] << std::endl;
        std::cout << "param 2 " << client->getMessage()->getParams()[2] << std::endl;

        //std::string   msg = client->getMessage()->getParams()[2];
        //std::cout << "COMMENT is : " << msg << std::endl;
        std::string chan = client->getMessage()->getParams()[0];
    // std::cout << " Channel to kick from : " << client->getMessage()->getParams()[0] << std::endl;
        // std::cout << " Users to kick : " << chan << std::endl;
        std::vector<std::string> users = ft_split(client->getMessage()->getParams()[1], ",");

    std::cout << " users vector: " << users << std::endl;
        std::cout << "count = " << server->getChannels().count(chan) << std::endl;

        if (server->getChannels().count(chan) == 0)
                client->sendMsg(ERR_NOSUCHCHANNEL + client->getNick() + " " + chan + " :No such channel");
        else if (!client->getModes().find('o')->second)
            client->sendMsg(ERR_NOPRIVILEGES + client->getNick() +  " :Permission Denied- You're not an IRC operator");
        else {
                std::cout << "check existant users and kick then " << std::endl;
                for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); ++it) {
                    if (server->getClientByNick(*it) == NULL)// || server->getChannels()[chan].ifMemberbyNick(*it) == false)
                            client->sendMsg(ERR_USERNOTINCHANNEL + client->getNick() + chan + " " + *it  + " :They aren't on that channel");
                    else {
                        size_t i = client->getMessage()->getParams()[2].find(":");
                        std::string     msg = "";
                        if (i != std::string::npos)
                                msg = client->getMessage()->getParams()[2].substr(i + 1);
                        std::cout << "COMMENT is : " << msg << std::endl;
                        std::string str =  "KICK " + chan + " " + *it + " :" + msg;
                        std::cout<< "SHOW str to send : " << str << std::endl;
                        //a message to the concerned user
                        //server->getUserbyNick(client->getMessage()->getParams()[1])->sendMsg(str);
                        server->getClientByNick(*it)->sendMsg(str);
                        //send message to all users of the channel - broadcast
                        //server->getChannels()[chan].removeMember(server->getUserbyNick(*it));
                        Channel*	channel = server->getChannelByName(chan);
																								channel->removeMember(server->getClientByNick(*it));
																								channel->broadcast(client, str);
                    }
                }
        }
}

// if (server->getChannels()[chan]->getUser(nickname) == false)
//      no user nickname in channel chan;