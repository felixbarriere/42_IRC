#include "../../inc/utils.hpp"

// https://modern.ircdocs.horse/#nick-message

void	nick(Server *server, Client *client) {
	(void) server;

	// std::cout << "DEBUG ===> NICK function called"  << std::endl << std::endl;

	// check command syntax

	if (!client->getWelcome()) {
		client->setNick(client->getMessage()->getParams()[0]);
		return ;
	}
	if (client->getAuthorized() == true)
	{
		// utiliser send pour indiquer au client que le nickname à changé
		// client->sendMsg("NICK " + client->getMessage()->getParams()[0]);
		client->sendMsg("NICK " + client->getMessage()->getParams()[0]);
		client->setNick(client->getMessage()->getParams()[0]);
	}
	

	// créer un vector dans Server pour enregistrer les userName et nickNames existants

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