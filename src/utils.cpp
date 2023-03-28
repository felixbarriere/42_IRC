#include "utils.hpp"

std::string	ft_trim(std::string	str, char toTrim) {
	std::string	temp;
	if (str[str.size() - 1] == toTrim )
		temp = str.substr(1, (str.size() - 2));
	else
		temp = str.substr(1, str.size());
	return (temp);
}

bool	checkCommand(std::string str) {
	for (int i = 0; str[i] ; i++) {
		if ((isalnum(str[i]) == 0) && str[i] != '{' && str[i] != '}' \
			&& str[i] != '[' && str[i] != ']' \
			&& str[i] != '_')
			return (false);
	}
	return (true);
}

bool checkMode(Client* client) {
    std::map<char, bool>::iterator	ret = client->getModes().find('o');
	return (ret->second);
}

int	checkPort(char* port) {
	std::string	portNumber = std::string(port);
	if (portNumber.size() != 4 || \
		portNumber.find_first_not_of("0123456789") != std::string::npos || \
		atoi(portNumber.c_str()) < 1024)
		return (1);
	return (0);
}
