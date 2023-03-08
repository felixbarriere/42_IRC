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

Message::Message() //:_message(NULL), _prefix(), _cmd(), _params()
{
	std::cout << "Default constructor MESSAGE" << std::endl << std::endl;
}

Message::Message(Client *client)
{
	this->_client = client;
	std::cout << "constructor MESSAGE" << std::endl << std::endl;
}

Message::Message(const Message &src):_message(src._message), _prefix(src._prefix), _cmd(src._cmd), _params(src._params)
{}

Message &Message::operator=(const Message &rhs)
{
	if(this != &rhs)
	{
		this->_message = rhs.getMessage();
		this->_cmd = rhs.getCmd();
	}
	return *this;
}

Message::~Message()
{}

/**********************************************************************************************************/
/*                                                Méthodes                                                */
/**********************************************************************************************************/

int Message::tokenizer(std::string line)
{
	// std::cout <<  std::endl << "test Tokenizer, line: "  << line << std::endl;
	
	this->_cmd.clear();
	this->_params.clear();

	std::vector<std::string>	temp = ft_split(line, " ");

	if (temp.size() == 2)
	{
			this->_cmd = temp[0];
			this->_params.push_back(temp[1]);
	}
	else	// la value est constituée de plusieurs strings (ex: USER)
	{
		this->_cmd = temp[0];
		std::vector<std::string>::iterator	it = temp.begin() + 1;
		for (; it != temp.end(); it++)
			this->_params.push_back(*it);
	}
	return (0);
}

void Message::createMessage()
{
	std::vector<std::string>	lines(ft_split(this->_client->getBuffer(), "\n\r"));

	for(unsigned long i = 0; i < lines.size() ; i++)
	{
		// répartir la ligne en _cmd et _params
		if (tokenizer(lines[i]) != 0)
		{
			std::cout << "Error tokenizer" << std::endl;
			break ;		// delete le message?
		}

		// check cmd then call command function
		std::map<std::string, fct_cmd>::iterator	ite;
		ite = _client->getServer()->getCommandList().end();

		if (_client->getServer()->getCommandList().find(_cmd) != ite)
		{
			// std::cout << "CMD " << _cmd << " EXISTS" << std::endl;
			_client->getServer()->getCommandList()[_cmd](_client->getServer(), _client);
		}
		// else
		// 	std::cout << "CMD " << _cmd << " doesn't EXISTS :(" << std::endl;
	}
}

/*******************************************************************************************************************/
/*                                                Getters / Setters                                                */
/*******************************************************************************************************************/


void Message::setPrefix(std::string prefix)
{
	this->_prefix = prefix;
}

void Message::setCmd(std::string cmd)
{
	this->_cmd = cmd;
}

void Message::setParams(std::vector<std::string> params)
{
	this->_params = params;
}

std::string Message::getMessage(void) const
{
	return (this->_message);
}

std::string Message::getPrefix(void) const
{
	return (this->_client->getNick() + "!" + this->_client->getUser() + "@" + this->_client->getHostname() + " ");
}

std::string Message::getCmd(void) const
{
	return (this->_cmd);
}

std::vector<std::string> Message::getParams(void) const
{
	return (this->_params);
}

std::ostream &operator<<(std::ostream &out, Message &data)
{
	out << "Prefix : "<< data.getPrefix() << "CMD : " << data.getCmd();
	return out;
}




/* *************************************************************************** */

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

 	TRIM: utile pour le username? Ou irssi le gere tout seul?
	if (checkCommand(temp[1]) == 2)		
	{
		if (temp[1][0] == '\"')
			temp[1] = ft_trim(temp[1], '\"');
		if (temp[1][0] == '\'')
			temp[1] = ft_trim(temp[1], '\'');
	}
	
 */

