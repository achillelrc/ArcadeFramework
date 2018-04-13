//
// EPITECH PROJECT, 2018
// firstry
// File description:
// Error.cpp
//

#include "Error.hpp"

Handler::Handler(const std::string &type, const std::string &msg) throw()
: location(type), message(msg)
{
}

const std::string Handler::what() throw()
{
	std::string tmp = "\033[1;31mERROR\033[0m in \033[1;35m";
	tmp += location;
	tmp += "\t\033[1;37m";
	tmp += message;
	tmp += "\033[0m\n";
	return (tmp);
}
