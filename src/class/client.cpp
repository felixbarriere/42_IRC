#include "utils.hpp"

Client::Client(): _c_socket(-1)
{	
	std::cout << "Default constructor CLIENT" << std::endl << std::endl;
}

Client::Client(int client_socket, struct sockaddr_in client_address) : _c_socket(client_socket), _c_address(client_address)
{
	std::cout << "Constructor CLIENT" << std::endl << std::endl;
}

Client::Client(const Client &src): _c_socket(-1)	//a changer si on utilise le const par copy
{
	(void)src;
}

Client &Client::operator=(const Client &rhs)
{
	(void)rhs;
	return *this;
}

Client::~Client() 
{	
	close(this->_c_socket);
	std::cout << "DEBUG ===> Destructor CLIENT" << std::endl << std::endl;
}

/************ Méthodes ************/
// void Client::addBuff(char buff_msg)
// {
// 	if (this->_buffer.find(_buffer) != std::string::npos)  // c'est pas ce qu'on fait dans la condition de receiveRequest?
// 		this->_buffer += _buffer;
// 	else
// 		return ;
// }

void	Client::createCommandList()
{
	std::cout << "DEBUG == > BUFFER CLIENT:" << std::endl << this->getBuffer() << std::endl;

	// spliter le buffer (separateurs = sauts a la ligne). Chaque ligne aura une key (nom de commande) et une value.

	std::vector<std::string>	lines(ft_split(this->getBuffer(), "\n\r"));

	for(int i = 0; i < lines.size() ; i++)
	{
		std::cout << "DEBUG == > FT_SPLIT CLIENT:" << i << " ==> " << lines[i] << std::endl;
		
		std::vector<std::string>	temp = ft_split(lines[i], " ");

		std::cout << "DEBUG == > mot 0:" << " ==> " << temp[0] << std::endl;
		std::cout << "DEBUG == > mot 1:" << " ==> " << temp[1] << std::endl;
		std::cout << std::endl;

		if (temp.size() == 2)
			this->_commands.insert(std::pair<std::string, std::string>( temp[0], temp[1]));
		else
		{
			// Attention: gérer le cas si la value est constituée de plusieurs strings (ex: USER)
			// pour trouver la string value, 	utiliser substr en enlevant temp[0].size() à line[i]
			std::string line2 = lines[i].substr(temp[0].size() + 1, (lines[i].size() - temp[0].size()));
			std::cout << "DEBUG == > temp[0]:" << " ==> " << temp[0] << std::endl;
			std::cout << "DEBUG == > line2:" << " ==> " <<  line2 << std::endl;

			this->_commands.insert(std::pair<std::string, std::string>( temp[0], line2));

			line2.clear();
		}
		temp.clear();
		// creer erreur si character particulier
	}
	std::cout << std::endl;
	std::cout << "DEBUG == > command CAP:" << " ==> " << this->_commands["CAP"] << std::endl;
	std::cout << "DEBUG == > command PWD:" << " ==> " << this->_commands["PWD"] << std::endl;
	std::cout << "DEBUG == > commands NICK:" << " ==> " << this->_commands["NICK"] << std::endl;
	std::cout << "DEBUG == > commands USER:" << " ==> " << this->_commands["USER"] << std::endl;

	// stocker les différents résultats dans une map< commandName, command >
	// clear this->_buffer.
}

/************ Getters / Setters ************/
int Client::getC_socket() const
{
	return (this->_c_socket);
}

struct sockaddr_in Client::getSockaddr_in() const
{
	return (this->_c_address);
}

std::string Client::getBuffer() const
{
	return (this->_buffer);
}

void Client::setBuffer(std::string str)
{
	this->_buffer = str;
}


