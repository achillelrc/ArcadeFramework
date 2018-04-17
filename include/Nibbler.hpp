//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Nibbler.hpp
//

#ifndef NIBBLER_HPP_
# define NIBBLER_HPP_

#include <string.h>
#include <unistd.h>
#include <fstream>
#include "DefaultKeys.hpp"
#include <fstream>
#include <cmath>
#include <iostream>
#include "IGameModule.hpp"
#include "ITilemap.hpp"
#include "Paths.hpp"

#define NIBL_LVL1 std::string("lvl1.nibbler")
#define NIBL_LVL2 std::string("lvl2.nibbler")
#define NIBL_LVL3 std::string("lvl3.nibbler")

class NibblerTilemap : public ITilemap {
public:
	NibblerTilemap();
	~NibblerTilemap();
	int getScale() const;
	std::map<char, std::pair<int, int> > getTilemap() const;
	std::string getTilemapPath() const;
private:
	std::map<char, std::pair<int, int> > _tilemap;
	std::string _path;
	int _scale;
};

class Nibbler : public IGameModule {
public:
	enum NibblerDir_e {
		NONE_DIR,
		RIGHT_DIR,
		LEFT_DIR,
		UP_DIR,
		DOWN_DIR
	};
	Nibbler();
	~Nibbler();
	void init();
	void setHandler(void *);
	void *getHandler() const;
	void setGraphicalLib(IDisplayModule *);
	const std::string &getName() const;
	int runGame();
	void keyAction(std::string);
	const std::vector<std::string> getGameMap() const;
	void initMap(const std::string &);
	const std::vector<objPos_t> getObjPos() const;
	int getScore() const;
	void saveScore() const;
	std::string getUserName() const;
	ITilemap *getTilemap() const;
	std::pair<double, double> getMapSize() const;
	void NibblerTick();
	void updateTail();
	void updateFood();
	NibblerDir_e calcDir();

private:
	IDisplayModule *_graphicModule;
	NibblerTilemap *_tilemap;
	int _state;
	void *_handler;
	std::string _name;
	std::vector<std::string> _gameMap;
	std::vector<objPos_t> _objMap;
	std::vector<objPos_t> _foodMap;
	int _score;
	int _maxCells;
	std::pair<double, double> _mapSize;
	NibblerDir_e _pDir;
	NibblerDir_e _NibblerDir;
	std::vector<std::vector<objPos_t>> _TailsPos;
};

#endif // NIBBLER_HPP_
