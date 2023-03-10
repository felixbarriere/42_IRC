#include "../../inc/utils.hpp"

// https://modern.ircdocs.horse/#nick-message

void	nick(Server *server, Client *client) {
	(void) server;

	// && checkCommand(client->getMessage()->getParams()[0]) == true
	if (!client->getWelcome()) 
	{
		if (checkCommand(client->getMessage()->getParams()[0]) == false)
			client->sendMsg(ERR_ERRONEUSNICKNAME " Erroneous nickname");
		else if (server->nickIsUsed(client->getMessage()->getParams()[0]) == true)
		{
			std::cout << "DEBUG ===> nickname already used"   << std::endl;
			client->sendMsg(ERR_NICKNAMEINUSE + client->getMessage()->getParams()[0] + " " + client->getMessage()->getParams()[0]);
		}
		else
			client->setNick(client->getMessage()->getParams()[0]);
		return ;
	}
	
	if (client->getMessage()->getParams().size() == 0)
	{
		client->sendMsg(ERR_NONICKNAMEGIVEN " : No nickname given");  // normalement irssi n'envoie rien dans ce cas
	}
	else if (checkCommand(client->getMessage()->getParams()[0]) == false)
	{
		std::cout << "DEBUG ===> Erroneous nickname"  << std::endl << std::endl;
		std::cout << "DEBUG ===> nickname: " << client->getMessage()->getParams()[0] << std::endl << std::endl;
		client->sendMsg(ERR_ERRONEUSNICKNAME + client->getNick() + " : Erroneous nickname");
	}
	else if (server->nickIsUsed(client->getMessage()->getParams()[0]) == true)
	{
		std::cout << "DEBUG ===> nickname already used 2"  << std::endl << std::endl;
		client->sendMsg(ERR_NICKNAMEINUSE + client->getMessage()->getParams()[0] + " " + client->getMessage()->getParams()[0] );
	}
	else if (client->getAuthorized() == true)
	{
		client->sendMsg("NICK " + client->getMessage()->getParams()[0]);
		client->setNick(client->getMessage()->getParams()[0]);

		// ajouter un broadcast pour avertir les membres du channel concernĂ© d'un nouveau nickname
		if (client->getChannel() != NULL)
		{
			// std::map<std::string, Channel>::iterator	it = server->getChannels().begin();
			// while (;it != server->getChannels().end(); it++) 
			// {
			// 	if ( it == client->getChannel())
				client->getChannel()->broadcast(client, " changed nickname to " + client->getMessage()->getParams()[0]);
			// }
		}
	}
}

// solutions: tester une boucle sur send()
// solutions: envoyer nickname au lieu de prefix
// solutions: manque le num RPL?
// solutions: le client attend d'abord un PONG du server pour etre sur que la communication est ok?

// ATTENTION: si meme syntaxe, renvoyer 433 et irssi se charge lui meme d'ajouter un "_"


// NICK ==> irssi indique le Nickname, pas d'envoi au serveur?
// NICK felix ==> NICK : CMD, felix: params
// NICK "felix"
// NICK 'felix'
// NICK "felix'

// Numeric Replies:

//            ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//            ERR_NICKNAMEINUSE               ERR_NICKCOLLISION

//    Example:

//    NICK Wiz                        ; Introducing new nick "Wiz".

//    :WiZ NICK Kilroy                ; WiZ changed his nickname to Kilroy.

/* 
Si on garde checkCommand lors de la reception des commandes depuis irssi lors de la connexion:

if (temp.size() == 2)
	{
		if (checkCommand(temp[1]) == 0)		//checkcommand utile du coup?
		{
			this->_cmd = temp[0];
			this->_params.push_back(temp[1]);
		}
		else if (checkCommand(temp[1]) == 1)
		{
			std::cout << "Erroneous value, please try again." << std::endl;
			return (1);
		}
	}

 	TRIM: utile pour le username? IRSSI gere tout seul
	if (checkCommand(temp[1]) == 2)		
	{
		if (temp[1][0] == '\"')
			temp[1] = ft_trim(temp[1], '\"');
		if (temp[1][0] == '\'')
			temp[1] = ft_trim(temp[1], '\'');
	}
	
 */