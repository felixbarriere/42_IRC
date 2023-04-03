#include "utils.hpp"

std::vector<std::string>	ft_split(const std::string& str, const std::string& sep) {
	std::string					str2 = str;
	std::vector<std::string>	ret;
	char*						buffer = strdup(str2.c_str());
	char*						sep2 = strdup(sep.c_str());
	char*						ptr = strtok(buffer, sep2);
	int							i = 0;
	while (ptr) {
		i++;
		ret.push_back(ptr);
		ptr = strtok(NULL, sep2);  
	}
	free(buffer);
	free(sep2);
	return (ret);
}
