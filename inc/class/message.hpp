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

//The extracted message is parsed into the components <prefix>,
//  <command> and list of parameters (<params>).
//https://www.tech-invite.com/y25/tinv-ietf-rfc-2812.html#e-2-3-1

//to put class Message into class Client ?!


#ifndef MESSAGE_HPP
# define MESSAGE_HPP

class Message {

	public:
	
		/************ Member functions ************/
		Message();
		Message(Client *client);
		Message(const std::string cmd);
		Message(const Message &src);
		Message &operator=(const Message &rhs);
		~Message();

		void 	createMessage();
		void	tokenizer(std::string line);		// peupler les attributs puis appeler la fonction correspondante. On reset le tout a chaque commande.
		
		/************ Getters / Setters ************/
		void setPrefix(std::string prefix);
		void setCmd(std::string cmd);
		void setParams(std::vector<std::string> params);

		std::string 				getMessage(void) const;
		std::string 				getPrefix(void) const;
		std::string 				getCmd(void) const;
		std::vector<std::string>	&getParams(void);

	private:

		/************ Attributes ************/
		Client						*_client;
		std::string					_message;   //buffer
		std::string 				_prefix;	//"Le pr??fix n'est utilis?? que pour un message provenant d'un serveur, il doit ??tre ignor?? s'il provient d'un client."
		std::string					_cmd;
		std::vector<std::string>	_params;

};

std::ostream &operator<<(std::ostream &out, Message &data);

#endif
