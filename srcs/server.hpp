class server
{
	public:

		server();
		server(char* portNumber);
		~server();

		void	setPortNumber(char * portNumber);
	private:
		char *	portNumber;
};