
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
essage typically has the form: "Killed (<killer> (<reason>))" where <killer> is 
he nickname of the user who performed the KILL. The user being killed then
receives the ERROR message, typically containing a <reason> of "Closing Link:
<servername> (Killed (<killer> (<reason>)))". After this, their connection is closed.
If a KILL message is received by a client, it means that the user specified by
<nickname> is being killed. With certain servers, users may elect to receive KILL
messages created for other users to keep an eye on the network. This behavior may also be restricted to operators.
Clients can rejoin instantly after this command is performed on them. However,
it can serve as a warning to a user to stop their activity. As it breaks the flow of data from the user,
it can also be used to stop large amounts of ‘flooding’ from abusive users or due to accidents.
Abusive users may not care and promptly reconnect and resume their abusive behaviour.
In these cases, opers may look at the KLINE command to keep them from rejoining the network for a longer time.
As nicknames across an IRC network MUST be unique, if duplicates are found when servers join,
one or both of the clients MAY be KILLed and removed from the network.
Servers may also handle this case in alternate ways that don’t involve removing users from the network.
Servers MAY restrict whether specific operators can remove users on other servers (remote users).
If the operator tries to remove a remote user but is not privileged to, they should receive the ERR_NOPRIVS (723) numeric.
<comment> SHOULD reflect why the KILL was performed. For user-generated KILLs, it is up to the user to provide an adequate reason.

Numeric Replies:
ERR_NOSUCHSERVER (402)
ERR_NEEDMOREPARAMS (461)
ERR_NOPRIVILEGES (481)
ERR_NOPRIVS (723) */

#include "../../inc/utils.hpp"

void ft_kill(Server *server, Client *client)
{
    if (server == NULL)
        return ;

    std::cout << "DEBUG ===> KILL called"  << std::endl << std::endl;

    if (client->getMessage()->getParams().size() < 2)
    {
        std::cout << "DEBUG ===> "  << std::endl << std::endl;
       client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Not enough parameters");
    }
   // else if(client->getNick() == NULL)
     //   client->sendMsg(ERR_NOSUCHNICK + client->getNick() + " : this client does not exist");
   /* else if(si mode du client n'est pas o ().find("o") == std::string::npos )
        client->sendMsg(ERR_NOPRIVILEGES + client->getNick() + " : this client does not have privileges to kill");
    else
    {
        std::cout << " KILL THE USER " << std::endl; 
        client->sendMsg(client->getNick() + " : you've been killed");
    }*/
       
}