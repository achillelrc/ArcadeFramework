//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// IGameModule.hpp
//

#ifndef IGAMEMODULE_HPP_
# define IGAMEMODULE_HPP_

#include <string>
#include <vector>
#include "IDisplayModule.hpp"
#include "ITilemap.hpp"

typedef struct objPos_s {
	double x;
	double y;
	char value;
	std::string name;
} objPos_t;

class IGameModule {
public:
	virtual ~IGameModule() = default;
	virtual void init() = 0;
	virtual void setHandler(void *) = 0;
	virtual void *getHandler() const = 0;
	virtual void setGraphicalLib(IDisplayModule *) = 0;
	virtual const std::string &getName() const = 0;
	virtual void keyAction(std::string) = 0;
	virtual const std::vector<std::string> getGameMap() const = 0;
	virtual const std::vector<objPos_t> getObjPos() const = 0;
	virtual int getScore() const = 0;
	virtual std::string getUserName() const = 0;
	virtual void saveScore() const = 0;
	virtual ITilemap *getTilemap() const = 0;
	virtual int runGame() = 0;
	virtual std::pair<double, double> getMapSize() const = 0;
};
#endif // IGAMEMODULE_HPP_
