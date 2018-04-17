//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// Arcade.cpp
//

#include <iterator>
#include "Paths.hpp"
#include "Arcade.hpp"
#include <algorithm>
#include "Error.hpp"
#include <dlfcn.h>
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <fstream>

const std::string &MyArcade::getNextGame()
{
	_indexGames++;
	if ((unsigned int)_indexGames >= _gameLibName.size()) {
		_indexGames = 0;
	}
	return (_gameLibName[_indexGames]);
}

const std::string &MyArcade::getNextGraphic()
{
	_indexGraphics++;
	if ((unsigned int)_indexGraphics >= _graphicLibName.size()) {
		_indexGraphics = 0;
	}
	return (_graphicLibName[_indexGraphics]);
}

const std::string &MyArcade::getPrevGame()
{
	_indexGames--;
	if (_indexGames < 0) {
		_indexGames = _gameLibName.size() - 1;
	}
	return (_gameLibName[_indexGames]);
}

const std::string &MyArcade::getPrevGraphic()
{
	_indexGraphics--;
	if (_indexGraphics < 0) {
		_indexGraphics = _graphicLibName.size() - 1;
	}
	return (_graphicLibName[_indexGraphics]);
}

MyArcade::MyArcade(char *graphicLib) : 	_indexGraphics(0), _indexGames(0)
{
	std::string libPath(graphicLib);
	std::string libName;

	libName = loadGraphicLibs(libPath);
	loadGameLibs();
	setGraphicLib(libName);
}

void MyArcade::nextGameLib()
{
	setGameLib(this->getNextGame());
}

void MyArcade::nextGraphicLib()
{
	setGraphicLib(this->getNextGraphic());
}

void MyArcade::prevGraphicLib()
{
	setGraphicLib(this->getPrevGraphic());
}

void MyArcade::prevGameLib()
{
	setGameLib(this->getPrevGame());
}

void MyArcade::run()
{
	int menuValidate = 0;
	int runGame = 0;

	while (1) {
		while (!menuValidate)
		menuValidate = this->_currentGraphicLib->displayMenu();
		runGame = 1;
		while (runGame != 0) {
			this->_currentGameLib->init();
			runGame = this->_currentGameLib->runGame();
		}
		menuValidate = 0;
	}
}

MyArcade::~MyArcade()
{
	this->_currentGraphicLib->destroy();
	this->unloadGameLib();
	this->unloadGraphicLib();
}

std::vector<std::string> loadLibFromDirectory(std::string path, const std::string &initLib)
{
	DIR *dir;
	struct dirent *ent;
	std::vector<std::string> libPaths;
	std::string fullPath;

	libPaths.push_back(initLib);
	if ((dir = opendir (path.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			fullPath = path + std::string(ent->d_name);
			if (fullPath.find(".so") != std::string::npos && initLib != fullPath) {
				libPaths.push_back(fullPath);
			}
		}
		closedir (dir);
	}
	else {
		throw Handler("MyArcade::loadLibFromDirectory", "error while reading " + path + " directory");
	}
	return (libPaths);
}

std::vector<std::string> loadLibFromDirectory(std::string path)
{
	DIR *dir;
	struct dirent *ent;
	std::vector<std::string> libPaths;
	std::string fullPath;

	if ((dir = opendir (path.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			fullPath = path + std::string(ent->d_name);
			if (fullPath.find(".so") != std::string::npos) {
				libPaths.push_back(fullPath);
			}
		}
		closedir (dir);
	}
	else {
		throw Handler("MyArcade::loadLibFromDirectory", "error while reading " + path + " directory");
	}
	return (libPaths);
}

std::string MyArcade::loadGraphicLibs(const std::string &initLib)
{
	graphicLib graphicCreator;
	std::vector<std::string> libsToLoad;
	unsigned int i = 0;
	char *error;
	void *graphicHandle;
	std::string initName;

	libsToLoad = loadLibFromDirectory(GRAPHICS_PATH, initLib);
	while (i < libsToLoad.size()) {
		graphicHandle = dlopen(libsToLoad[i].c_str(), RTLD_NOW);
		if (!graphicHandle) {
			throw Handler("MyArcade::loadGraphicLibs", std::string(dlerror()));
		}
		graphicCreator = (graphicLib)dlsym(graphicHandle, "LibEntryPoint");
		if ((error = dlerror()) != NULL) {
			throw Handler("MyArcade::loadGraphicLibs", std::string(error));
		}
		(*graphicCreator)()->setHandler(graphicHandle);
		this->_graphicLibraries[(*graphicCreator)()->getName()] = (*graphicCreator)();
		this->_graphicLibName.push_back((*graphicCreator)()->getName());
		if (i == 0)
			initName = (*graphicCreator)()->getName();
		i++;
	}
	return (initName);
}

void MyArcade::pushGraphicName()
{
	this->_currentGraphicLib->setGraphicLibName(std::vector<std::string>(this->_graphicLibName));
}

void MyArcade::pushGameName()
{
	this->_currentGraphicLib->setGameLibName(std::vector<std::string>(this->_gameLibName));
}

void MyArcade::pushScores()
{
	std::vector<std::string> array;
	std::ifstream file;
	std::string line;
	std::string fileName;

	if (!this->_currentGameLib)
		return;
	fileName = SCORE_PATH + this->_currentGameLib->getName();
	file.open(fileName);
	while (getline(file, line)) {
		array.push_back(line);
	}
	this->_currentGraphicLib->setScore(array);
	file.close();
}

void MyArcade::loadGameLibs()
{
	gameLib gameCreator;
	std::vector<std::string> libsToLoad;
	unsigned int i = 0;
	char *error;
	void *gameHandle;

	libsToLoad = loadLibFromDirectory(GAMES_PATH);
	while (i < libsToLoad.size()) {
		gameHandle = dlopen(libsToLoad[i].c_str(), RTLD_NOW);
		if (!gameHandle) {
			throw Handler("MyArcade::loadGameLibs", std::string(dlerror()));
		}
		gameCreator = (gameLib)dlsym(gameHandle, "GameEntryPoint");
		if ((error = dlerror()) != NULL) {
			throw Handler("MyArcade::loadGameLibs", std::string(error));
		}
		(*gameCreator)()->setHandler(gameHandle);
		this->_gameLibraries[(*gameCreator)()->getName()] = (*gameCreator)();
		this->_gameLibName.push_back((*gameCreator)()->getName());
		i++;
	}
}


void MyArcade::setGraphicLib(const std::string &libName)
{
	if (this->_currentGraphicLib)
		this->_currentGraphicLib->destroy();
	this->_currentGraphicLib = this->_graphicLibraries[libName];
	if (!this->_currentGraphicLib) {
		throw Handler("MyArcade::setGraphicLib", "graphic library error");
	}
	_indexGraphics = find(_graphicLibName.begin(), _graphicLibName.end(), libName) - _graphicLibName.begin();
	this->_currentGraphicLib->init(this);
	if (_currentGameLib)
		this->_currentGameLib->setGraphicalLib(this->_currentGraphicLib);
}

void MyArcade::setGameLib(const std::string &libName)
{
	this->_currentGameLib = this->_gameLibraries[libName];
	if (!this->_currentGameLib) {
		throw Handler("MyArcade::setGameLib", "game library error");
	}
	_indexGames = find(_gameLibName.begin(), _gameLibName.end(), libName) - _gameLibName.begin();
	this->_currentGameLib->init();
	this->_currentGameLib->setGraphicalLib(this->_currentGraphicLib);
}

void MyArcade::unloadGameLib()
{
	auto it = _gameLibraries.begin();

	while (it != _gameLibraries.end()) {
		dlclose((*it).second->getHandler());
		it++;
	}
}

void MyArcade::unloadGraphicLib()
{
	auto it = _graphicLibraries.begin();

	while (it != _graphicLibraries.end()) {
		dlclose((*it).second->getHandler());
		it++;
	}
}
