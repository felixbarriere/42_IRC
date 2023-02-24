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

Message::Message():_message(NULL), _cmd()
{}

//Message::Message(arg){}

Message::Message(const Message &src):_message(src._message), _cmd(src._cmd)
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

void Message::setCmd(std::string cmd)
{
	this->_cmd = cmd;
}

std::string Message::getMessage(void) const
{
	return (this->_message);
}

std::string Message::getCmd(void) const
{
	return (this->_cmd);
}

std::ostream &operator<<(std::ostream &out, Message &data)
{
	out << "CMD : " << data.getCmd();
	return out;
}