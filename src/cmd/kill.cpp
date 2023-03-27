
/*KILL message

     Command: KILL
  Parameters: <nickname> <comment>

The KILL command is used to close the connection between a given client and the server they are connected to.
KILL is a privileged command and is available only to IRC Operators. <nickname> represents the user to be ‘killed’,
and <comment> is shown to all users and to the user themselves upon being killed.
When a KILL command is used, the client being killed receives the KILL message,
and the <source> of the message SHOULD be the operator who performed the command.
The user being killed and every user sharing a channel with them receives a QUIT
message representing that they are leaving the network. The <reason> on this QUIT 
message typically has the form: "Killed (<killer> (<reason>))" where <killer> is 
he nickname of the user who performed the KILL. The user being killed then
receives the ERROR message, typically containing a <reason> of "Closing Link:
<servername> (Killed (<killer> (<reason>)))". After this, their connection is closed.
If a KILL message is received by a client, it means that the user specified by
<nickname> is being killed. With certain servers, users may elect to receive KILL
messages created for other users to keep an eye on the network. This behavior may also be restricted to operators.
Clients can rejoin instantly after this command is performed on them.
If the operator tries to remove a remote user but is not privileged to, 
they should receive the ERR_NOPRIVS (723) numeric.
<comment> SHOULD reflect why the KILL was performed. 
For user-generated KILLs, it is up to the user to provide an adequate reason.

Numeric Replies:
ERR_NOSUCHSERVER (402)
ERR_NEEDMOREPARAMS (461)
ERR_NOPRIVILEGES (481)
ERR_NOPRIVS (723) */

#include "../../inc/utils.hpp"

void ft_kill(Server* server, Client* client) {
    if (!server)
        return ;
    std::cout << "DEBUG ===> KILL called"  << std::endl << std::endl;
    // std::cout << "DEBUG ===> nickname to kill " << client->getMessage()->getParams()[0] << std::endl << std::endl;
    // std::cout << "DEBUG ===> killer's modes are : " << client->getModes() << std::endl << std::endl;
    if (client->getMessage()->getParams().size() < 2)
        client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Not enough parameters");
    else if (!server->getUserbyNick(client->getMessage()->getParams()[0]))
        client->sendMsg(ERR_ERRONEUSNICKNAME + client->getNick() + " " + client->getMessage()->getParams()[0] + " :No such nickname");
    //else if(checkMode(client) == false)
    else if (!client->getModes().find('o')->second)
            client->sendMsg(ERR_NOPRIVILEGES + client->getNick() +  " :Permission Denied- You're not an IRC operator");
    else
    {
        size_t i = client->getMessage()->getParams()[1].find(":");
        std::string     comment = "";
        if (i != std::string::npos)
            comment = client->getMessage()->getParams()[1].substr(i + 1);
        //std::string comment = client->getMessage()->getParams()[1];
        std::cout << "CHECK===> comment =  " << comment << std::endl;
        std::string str_to_all = "Killed ( " + client->getNick() + " " + comment + " )";
        std::string str_to_user = "Closing Link: " +  client->getHostname() + " (Killed ( " + client->getNick() + " " + comment + " )";
		//send the KILL message to user killed
		server->getUserbyNick(client->getMessage()->getParams()[0])->sendMsg(str_to_user);
        //send the QUIT msg to everyone in the channel - in cmd quit->broadcast
        quit(server, server->getUserbyNick(client->getMessage()->getParams()[0]));
        //kick(server, server->getUserbyNick(client->getMessage()->getParams()[0]));
    }
}