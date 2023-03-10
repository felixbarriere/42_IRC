#include "utils.hpp"


std::string	ft_trim(std::string	str, char toTrim)	// useless, irssi le fait tout seul
{
	std::string temp;

	if (str[str.size() - 1] == toTrim )
		temp = str.substr(1, (str.size() - 2));
	else
		temp = str.substr(1, str.size());

	return (temp);
}

bool	checkCommand(std::string	str)
{
	// if (str[0] == '\"' || str[0] == '\'')   //"felix" et 'felix' ==> acceptés mais "felix' ==> error
	// 	return (2);
	std::cout << "DEBUG ===> check nick: " << str << std::endl << std::endl;

	for (int i = 0; str[i] ; i++)
	{
		// {} and [] accepted in irssi
		if ((isalnum(str[i]) == 0) && str[i] != '{' && str[i] != '}'
									&& str[i] != '[' && str[i] != ']')
			return (false);
	}
	return (true);
}