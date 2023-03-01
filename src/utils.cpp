#include "utils.hpp"


std::string	ft_trim(std::string	str, char toTrim)
{
	std::string temp;

	if (str[str.size() - 1] == toTrim )
		temp = str.substr(1, (str.size() - 2));
	else
		temp = str.substr(1, str.size());

	return (temp);
}

int	checkCommand(std::string	str)
{
	if (str[0] == '\"' || str[0] == '\'')   //"felix" et 'felix' ==> acceptés mais "felix' ==> error
		return (2);

	for (int i = 0; str[i] ; i++)
	{
		// {} and [] accepted in irssi
		if ((isalnum(str[i]) == 0) && str[i] != '{' && str[i] != '}'
									&& str[i] != '[' && str[i] != ']')
			return (1);
	}

	return (0);
}