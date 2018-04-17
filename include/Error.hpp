//
// EPITECH PROJECT, 2018
// firstry
// File description:
// Error.hpp
//

#ifndef _ERROR_HPP_
# define _ERROR_HPP_

#include <iostream>
#include <exception>

class Handler : public std::exception
{
public:
	Handler(const std::string &type = "",
		const std::string &msg = "") throw();
	virtual ~Handler() throw() { };
	virtual const std::string what() throw();
private:
	using std::exception::what;
	std::string location;
	std::string message;
};

#endif /* !_ERROR_HPP_ */
