/*OPER message

     Command: OPER
  Parameters: <name> <password>
  
The OPER command is used by a normal user to obtain IRC operator privileges. 
Both parameters are required for the command to be successful.
If the client does not send the correct password for the given name, 
the server replies with an ERR_PASSWDMISMATCH message and the request is not successful.
If the client is not connecting from a valid host for the given name, 
the server replies with an ERR_NOOPERHOST message and the request is not successful.
If the supplied name and password are both correct, and the user is connecting from a valid host, 
the RPL_YOUREOPER message is sent to the user. 
The user will also receive a MODE message indicating their new user modes, and other messages may be sent.
The <name> specified by this command is separate to the accounts specified by SASL authentication,
and is generally stored in the IRCd configuration.

Numeric Replies:
ERR_NEEDMOREPARAMS (461)
ERR_PASSWDMISMATCH (464)
ERR_NOOPERHOST (491)
RPL_YOUREOPER (381)*/

#include "../../inc/utils.hpp"

void oper(Server* server, Client* client) {
    if (!server)
        return ;
    // std::cout << "DEBUG ===> OPER called from client #" << client->getC_socket()  << std::endl << std::endl;
    // std::cout << "DEBUG ===> PARAMS " << std::endl;
    // std::cout << "nick is : " << client->getMessage()->getParams()[0] << std::endl;
    // std::cout << "password is : " << client->getMessage()->getParams()[1]  << std::endl << std::endl;
    if (client->getMessage()->getParams().size() < 2)
       client->sendMsg(ERR_NEEDMOREPARAMS + client->getNick() + " :Not enough parameters");
    else if (client->getMessage()->getParams()[1] != OPER_PASSWORD)
      client->sendMsg(ERR_PASSWDMISMATCH + client->getNick() +  " :Password is incorrect");
    else if (client->getMessage()->getParams()[0] != OPER_USER)
      client->sendMsg(ERR_ERRONEUSNICKNAME + client->getNick() + " :Erroneus nickname");
    else {
      client->addMode('o');
      client->sendMsg(RPL_YOUREOPER + client->getNick() + " :You are now an IRC operator");
    }
}

// bool authenticateUser(std::string username, std::string password) {
//     if (username == "admin" && password == "password") 
//         return true;
//     else 
//         return false;
// }
