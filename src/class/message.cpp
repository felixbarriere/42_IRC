/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:58:59 by masamoil          #+#    #+#             */
/*   Updated: 2023/03/06 11:59:15 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

/***************************************************************************************************************************/
/*                                                Constructors / Destructor                                                */
/***************************************************************************************************************************/

Message::Message() {}

Message::Message(Client *client):
	_client(client) {}

Message::Message(const std::string cmd):
	_cmd(cmd) {}

Message::Message(const Message &src):
	_message(src._message),
	_prefix(src._prefix),
	_cmd(src._cmd),
	_params(src._params) {}

Message &Message::operator=(const Message &rhs) {
	if(this != &rhs) {
		_message = rhs.getMessage();
		_cmd = rhs.getCmd();
	}
	return (*this);
}

Message::~Message() {}

/**********************************************************************************************************/
/*                                                Méthodes                                                */
/**********************************************************************************************************/

void	Message::tokenizer(std::string line) {
	_cmd.clear();
	_params.clear();
	std::vector<std::string>	temp = ft_split(line, " ");
	if (temp.size() == 2) {
		_cmd = temp[0];
		_params.push_back(temp[1]);
	}
	else {	
		// la value est constituée de plusieurs strings (ex: USER)
		_cmd = temp[0];
		std::vector<std::string>::iterator	it = temp.begin() + 1;
		for (; it != temp.end(); it++)
			_params.push_back(*it);
	}
}

void Message::createMessage() {
	std::vector<std::string>	lines(ft_split(_client->getBuffer(), "\n\r"));
	for (unsigned long i = 0; i < lines.size() ; i++) {
		// répartir la ligne en _cmd et _params
		tokenizer(lines[i]);
		// if (tokenizer(lines[i]))
		// {
		// 	std::cout << "Error tokenizer" << std::endl;
		// 	break ;		// delete le message?
		// }
		// check cmd then call command function
		std::map<std::string, fct_cmd>::iterator	ite;
		ite = _client->getServer()->getCommandList().end();
		if (_client->getServer()->getCommandList().find(_cmd) != ite) {
			if (_client->getWelcome() || getCmd() == "PASS" || getCmd() == "NICK" || getCmd() == "USER")
				_client->getServer()->getCommandList()[_cmd](_client->getServer(), _client);
		}
		// else
		// 	std::cout << "CMD " << _cmd << " doesn't EXISTS :(" << std::endl;
	}
}

/*******************************************************************************************************************/
/*                                                Getters / Setters                                                */
/*******************************************************************************************************************/

void	Message::setPrefix(std::string prefix) { _prefix = prefix; }
void	Message::setCmd(std::string cmd) { _cmd = cmd; }
void	Message::setParams(std::vector<std::string> params) { _params = params; }

std::string					Message::getMessage() const { return (_message); }
std::string					Message::getCmd() const { return (_cmd); }
std::vector<std::string>	&Message::getParams() { return (_params); }

std::string		Message::getPrefix() const {
	return (_client->getNick() + "!" + _client->getUser() + "@" + _client->getHostname() + " ");
}
std::ostream	&operator<<(std::ostream &out, Message &data) {
	out << "Prefix : "<< data.getPrefix() << "CMD : " << data.getCmd();
	return (out);
}
