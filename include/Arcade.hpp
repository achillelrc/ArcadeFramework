//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// Arcade.hpp
//

#ifndef ARCADE_HPP_
# define ARCADE_HPP_

#include "ICoreProgram.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include <map>

typedef IDisplayModule* (*graphicLib)();
typedef IGameModule* (*gameLib)();

class MyArcade : public ICoreProgram
{
public:
	MyArcade(char *);
	~MyArcade();
	void loadGameLibs();
	std::string loadGraphicLibs(const std::string &);
	void setGraphicLib(const std::string &);
	void setGameLib(const std::string &);
	void unloadGameLib();
	void unloadGraphicLib();
	void run();
	void nextGraphicLib();
	void nextGameLib();
	void prevGraphicLib();
	void prevGameLib();
	const std::string &getNextGame();
	const std::string &getNextGraphic();
	const std::string &getPrevGame();
	const std::string &getPrevGraphic();
	void pushGraphicName();
	void pushGameName();
	void pushScores();
private:
	std::map<std::string, IDisplayModule *> _graphicLibraries;
	std::map<std::string, IGameModule *> _gameLibraries;
	std::vector<std::string> _graphicLibName;
	std::vector<std::string> _gameLibName;
	IDisplayModule *_currentGraphicLib;
	IGameModule *_currentGameLib;
	int _indexGraphics;
	int _indexGames;
};

#endif // ARCADE_HPP_
