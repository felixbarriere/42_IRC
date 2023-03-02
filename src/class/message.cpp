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

Message::Message():_message(NULL), _prefix(), _cmd(), _params()
{}

//Message::Message(arg){}

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

void Message::setMessage(std::string msg)
{
	this->_message = msg;
}

void Message::setPrefix(std::string prefix)
{
	this->_prefix = prefix;
}

void Message::setCmd(std::string cmd)
{
	this->_cmd = cmd;
}

void Message::setParams(std::string params)
{
	this->_params = params;
}

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

std::string Message::getParams(void) const
{
	return (this->_params);
}

std::ostream &operator<<(std::ostream &out, Message &data)
{
	out << "Prefix : "<< data.getParams() << "CMD : " << data.getCmd();
	return out;
}