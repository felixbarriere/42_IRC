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
	private:
		int						c_socket;
		struct sockaddr_in 		c_address;


};

#endif