#ifndef	CLIENT_HPP
#define CLIENT_HPP


class Client
{
	public:

		/************ Constructors / Destructor ************/
		Client();
		Client(int client_socket, struct sockaddr_in client_address);
		~Client();

		/************ Méthodes ************/



		/************ Getters / Setters ************/





		/************ Attributs ************/
		int						c_socket;	//a remettre private (getter a mettre)
	private:
		struct sockaddr_in 		c_address;


};

#endif