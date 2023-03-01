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
		//bool conn(std::string, int);
        // bool send_data(std::string data);
		//https://www.binarytides.com/code-a-simple-socket-client-class-in-c/

		/************ Getters / Setters ************/
		int 				getC_socket() const;
		std::string		 	getSockaddr_in() const;
		std::string 		getBuffer() const;
		std::string 		getUser() const;
		std::string 		getNick() const;
		std::string 		getHostname() const;
		
		void 				setBuffer(std::string str);
		void 				setUser(std::string str);
		void		 		setNick(std::string str);
		void		 		setHostname(std::string str);	//utile?



		/************ Attributs ************/
	private:
		//pour stocker l'integralite du message recu
		std::string							_buffer;
		std::string							_user;
		std::string							_nick;
		std::string							_hostname;
		int									_c_socket;
		std::string 						_c_address;
		std::map<std::string, std::string>	_commands;


};

#endif