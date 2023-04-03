
/*KILL message

     Command: KILL
  Parameters: <nickname> <comment>

https://www.tech-invite.com/y25/tinv-ietf-rfc-2812-2.html#e-3-7-1
https://modern.ircdocs.horse/#kill-message

Numeric Replies:
ERR_NOSUCHSERVER (402)
ERR_NEEDMOREPARAMS (461)
ERR_NOPRIVILEGES (481)
ERR_NOPRIVS (723) */

#include "../../inc/utils.hpp"

void ft_kill(Server* server, Client* client) {
    if (!server)
        return ;
    std::string str_to_all;
    if (client->getMessage()->getParams().size() < 2)
        client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Not enough parameters", client);
    else if (!server->getClientByNick(client->getMessage()->getParams()[0]))
        client->sendMsg(ERR_ERRONEUSNICKNAME + client->getNick() + " " + client->getMessage()->getParams()[0] + " :No such nickname", client);
    else if (!client->getModes().find('o')->second)
            client->sendMsg(ERR_NOPRIVILEGES + client->getNick() +  " :Permission Denied- You're not an IRC operator", client);
    else{
        size_t i = client->getMessage()->getParams()[1].find(":");
        std::string     comment = "";
        if (i != std::string::npos)
            comment = client->getMessage()->getParams()[1].substr(i + 1);
        std::string str_to_all = " KILL :" + comment;
        std::string str_to_user = " :Killed by " + client->getNick() + " because " + comment;
		// on delete les parametres du client qui se fait kill, puis on lui passe str_to_user
		server->getClientByNick(client->getMessage()->getParams()[0])->getMessage()->getParams().clear();
		server->getClientByNick(client->getMessage()->getParams()[0])->getMessage()->getParams().push_back(str_to_all);
		//send the KILL message to user killed
		server->getClientByNick(client->getMessage()->getParams()[0])->sendMsg(str_to_user, server->getClientByNick(client->getMessage()->getParams()[0]));
        //send the QUIT msg to everyone in the channel - in cmd quit->broadcast
        quit(server, server->getClientByNick(client->getMessage()->getParams()[0]));
		server->removeClient(server->getClientByNick(client->getMessage()->getParams()[0]), server->getClientByNick(client->getMessage()->getParams()[0])->getC_socket());
    }
	client->sendMsg(str_to_all, client);
}
