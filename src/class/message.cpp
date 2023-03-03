/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:58:59 by masamoil          #+#    #+#             */
/*   Updated: 2023/02/22 12:01:12 by masamoil         ###   ########.fr       */
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

void	Message::tempUserNick(std::string str)
{
	if (str == "USER")
		this->_client->setUser(str);
	if (str == "NICK")
	this->_client->setNick(str);
}

int Message::tokenizer(std::string line)
{
	std::cout <<  std::endl << "test Tokenizer, line: "  << line << std::endl << std::endl;
	
	this->_cmd.clear();
	this->_params.clear();

	std::vector<std::string>	temp = ft_split(line, " ");

	// fonction temporaire
	if (temp[0] == "USER" || temp[0] == "NICK")
		tempUserNick(temp[0]);

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
	else	// la value est constituée de plusieurs strings (ex: USER)
	{
		this->_cmd = temp[0];
		std::vector<std::string>::iterator	it = temp.begin() + 1;
		for (; it != temp.end(); it++)
			this->_params.push_back(*it);
	}
	return (0);

	// TRIM: utile pour le username? Ou irssi le gere tout seul?
	// 	if (checkCommand(temp[1]) == 2)		
	// 	{
	// 		if (temp[1][0] == '\"')
	// 			temp[1] = ft_trim(temp[1], '\"');
	// 		if (temp[1][0] == '\'')
	// 			temp[1] = ft_trim(temp[1], '\'');
	// 	}
}

/*******************************************************************************************************************/
/*                                                Getters / Setters                                                */
/*******************************************************************************************************************/

void Message::createMessage(std::string msg)
{
	std::vector<std::string>	lines(ft_split(this->_client->getBuffer(), "\n\r"));

	for(int i = 0; i < lines.size() ; i++)
	{
		if (tokenizer(lines[i]) != 0)
		{
			std::cout << "Error tokenizer" << std::endl;
			break ;		// delete le message?
		}

		std::cout << "test Tokenizer, CMD: " <<  _cmd << std::endl;

		std::vector<std::string>::iterator	it = _params.begin();
		for (; it != _params.end(); it++)
			std::cout << "test Tokenizer, params: " << *it << std::endl;
	}
}

void Message::setPrefix(std::string prefix)
{
	this->_prefix = prefix;
}

void Message::setCmd(std::string cmd)
{
	this->_cmd = cmd;
}

// void Message::setParams(std::string params)
// {
// 	this->_params = params;
// }

std::string Message::getMessage(void) const
{
	return (this->_message);
}

std::string Message::getPrefix(void) const
{
	return (this->_prefix);
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