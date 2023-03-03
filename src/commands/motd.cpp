/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:33:58 by masamoil          #+#    #+#             */
/*   Updated: 2023/03/03 10:34:00 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Command: MOTD
	Parameters: [ <target> ]

	The MOTD command is used to get the "Message Of The Day" of the given
	server, or current server if <target> is omitted.
	Wildcards are allowed in the <target> parameter.
	Numeric Replies:
			RPL_MOTDSTART                   RPL_MOTD
			RPL_ENDOFMOTD                   ERR_NOMOTD */

#include "utils.hpp"

void motd(Server *serv)
{
	(void)serv;
	std::vector<std::string> msgotd;
	std::string line;
	std::ifstream	ifs;
	ifs.open("../../media/motd.txt", std::ifstream::in);
	if(ifs.is_open())
	{
		while (getline(ifs, line))
			msgotd.push_back(line);
		for(std::vector<std::string>::iterator it = msgotd.begin(); it < msgotd.end(); it++)
			std::cout << *it << std::endl;
	}
	ifs.close();
}