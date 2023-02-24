/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:27:50 by masamoil          #+#    #+#             */
/*   Updated: 2023/02/22 13:28:38 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

class Message
{
	public:
		/************ Constructors / Destructor ************/
		Message();
		//Message(arg constructor);
		Message(const Message &src);
		Message &operator=(const Message &rhs);
		~Message();

		/************ Getters / Setters ************/
		void setMessage(std::string msg);
		void setCmd(std::string cmd);

		std::string getMessage(void) const;
		std::string getCmd(void) const;

		/************ Attributs ************/
	private:
		std::string	_message;
		std::string	_cmd;

	protected:

};

std::ostream &operator<<(std::ostream &out, Message &data);

#endif
