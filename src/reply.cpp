#include "../inc/utils.hpp"

void	reply(Client *client, std::string msg) {
	msg += "\r\n";
	const char	*m = msg.c_str();
	size_t		len = strlen(m);
	ssize_t		ret = 0;
	for (size_t sent = 0; sent < len; sent += ret) {
		ret = send(client->getC_socket(), &m[sent], len - sent, MSG_NOSIGNAL);
		if (ret == -1) {
			std::cout << "send() failed" << std::endl;
			return ;
		}
	}
}
