//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// IDisplayModule.hpp
//

#ifndef IDISPLAYMODULE_HPP_
# define IDISPLAYMODULE_HPP_

#include <string>
#include <vector>
#include "ICoreProgram.hpp"

class IGameModule;

class IDisplayModule {
public:
	virtual ~IDisplayModule() = default;
	virtual void init(ICoreProgram *) = 0;
	virtual void destroy() = 0;
	virtual void setHandler(void *) = 0;
	virtual void setGraphicLibName(std::vector<std::string>) = 0;
	virtual void setGameLibName(std::vector<std::string>) = 0;
	virtual void setScore(std::vector<std::string>) = 0;
	virtual void setUserName(std::string userName) = 0;
	virtual void *getHandler() const = 0;
	virtual const std::string &getName() const = 0;
	virtual const std::string &getUserName() const = 0;
	virtual void updateDisplay(IGameModule *) = 0;
	virtual int displayMenu() = 0;
	virtual void printText(std::string, long = 2000000) = 0;
	virtual std::string getKey() = 0;
	virtual void keyAction(std::string) = 0;
};

#endif // IDISPLAYMODULE_HPP_
