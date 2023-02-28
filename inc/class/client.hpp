#ifndef	CLIENT_HPP
#define CLIENT_HPP


class Client
{
	public:

		/************ Constructors / Destructor ************/
		Client();
		Client(const Client &src);
		Client &operator=(const Client &rhs);
		Client(int client_socket, struct sockaddr_in client_address);
		~Client();

		/************ Méthodes ************/
		void	addBuff(char buff_msg);
		void	welcome_msg();
		void	createCommandList();

		/************ Getters / Setters ************/
		int 				getC_socket() const;
		struct sockaddr_in 	getSockaddr_in() const;
		std::string 		getBuffer() const;
		
		void 				setBuffer(std::string str);

		/************ Attributs ************/
	private:
		//pour stocker l'integralite du message recu
		std::string							_buffer;
		std::string							_user;
		std::string							_nick;
		int									_c_socket;
		struct sockaddr_in 					_c_address;
		std::map<std::string, std::string>	_commands;


};

#endif