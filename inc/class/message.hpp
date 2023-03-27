//The extracted message is parsed into the components <prefix>,
//  <command> and list of parameters (<params>).
//https://www.tech-invite.com/y25/tinv-ietf-rfc-2812.html#e-2-3-1

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

class Message {

	public:
	
		/************ Member functions ************/
		Message();
		Message(Client*);
		Message(const std::string);
		Message(const Message&);
		Message &operator=(const Message&);
		~Message();

		void 	createMessage();
		void	tokenizer(std::string);		// peupler les attributs puis appeler la fonction correspondante. On reset le tout a chaque commande.
		
		/************ Getters / Setters ************/
		void setPrefix(std::string);
		void setCmd(std::string);
		void setParams(std::vector<std::string>);

		std::string 				getMessage() const;
		std::string 				getPrefix() const;
		std::string 				getCmd() const;
		std::vector<std::string>&	getParams();

	private:

		/************ Attributes ************/
		Client*						_client;
		std::string					_message;   //buffer
		std::string 				_prefix;	//"Le préfix n'est utilisé que pour un message provenant d'un serveur, il doit être ignoré s'il provient d'un client."
		std::string					_cmd;
		std::vector<std::string>	_params;

};

std::ostream &operator<<(std::ostream &out, Message &data);

#endif
