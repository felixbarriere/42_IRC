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
#define MESSAGE_HPP

class Message
{
	public:
		/************ Constructors / Destructor ************/
		Message();
		Message(Client *client);
		Message(const Message &src);
		Message &operator=(const Message &rhs);
		~Message();

		/************ Getters / Setters ************/
		void 	createMessage();
		int	 	tokenizer(std::string line);		// peupler les attributs puis appeler la fonction correspondante. On reset le tout a chaque commande.
		void	tempUserNick(std::string str);
		
		void setPrefix(std::string prefix);
		void setCmd(std::string cmd);
		void setParams(std::vector<std::string> params);

		std::string 				getMessage(void) const;
		std::string 				getPrefix(void) const;
		std::string 				getCmd(void) const;
		std::vector<std::string>	getParams(void) const;

		/************ Attributs ************/
	private:
		Client						*_client;
		std::string					_message;   //buffer
		std::string 				_prefix;	//"Le préfix n'est utilisé que pour un message provenant d'un serveur, il doit être ignoré s'il provient d'un client."
		std::string					_cmd;
		std::vector<std::string>	_params;

	protected:

};

std::ostream &operator<<(std::ostream &out, Message &data);

#endif
