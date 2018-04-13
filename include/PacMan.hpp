//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// PacMan.hpp
//

#ifndef PACMAN_HPP_
# define PACMAN_HPP_

#include "IGameModule.hpp"
#include "ITilemap.hpp"

class PacManTilemap : public ITilemap {
public:
	PacManTilemap();
	~PacManTilemap();
	int getScale() const;
	std::map<char, std::pair<int, int>> getTilemap() const;
	std::string getTilemapPath() const;
private:
	std::map<char, std::pair<int, int>> _tilemap;
	std::string _path;
	int _scale;
};

class PacMan : public IGameModule {
public:
	enum PacManDirection_e {
		NONE_DIR,
		RIGHT_DIR,
		LEFT_DIR,
		UP_DIR,
		DOWN_DIR
	};
	PacMan();
	~PacMan();
	void init();
	void setHandler(void *);
	void *getHandler() const;
	void setGraphicalLib(IDisplayModule *);
	const std::string &getName() const;
	int runGame();
	void keyAction(std::string);
	const std::vector<std::string> getGameMap() const;
	void initMap();
	std::vector<std::string> testfunc(std::vector<std::string> gameMap);
	const std::vector<objPos_t> getObjPos() const;
	int getScore() const;
	void saveScore() const;
	int hasTileMap() const;
	std::string getUserName() const;
	ITilemap *getTilemap() const;
	std::pair<double, double> getMapSize() const;
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void pacManTick();
	void loadPacGums();
	void eatPacGum();
	bool checkForWin();
	int detectGhostCollide();
	void initGhosts();
	PacManDirection_e calcDir();
	std::vector<PacMan::PacManDirection_e> calcAllDir(objPos_t, PacMan::PacManDirection_e);
	void moveGhosts();
	int ghostTick(int i, objPos_t &ghost, PacMan::PacManDirection_e dir);
	void ghostLock(bool = 0);
	void checkGodMode();
private:
	IDisplayModule *_graphicModule;
	PacManTilemap *_tilemap;
	int _state;
	void *_handler;
	std::string _name;
	std::vector<std::string> _gameMap;
	std::vector<objPos_t> _objMap;
	std::vector<objPos_t> _pacGums;
	std::vector<objPos_t> _ghosts;
	std::vector<PacMan::PacManDirection_e> _ghostsDir;
	int _score;
	std::pair<double, double> _mapSize;
	PacManDirection_e _pacManDir;
	PacManDirection_e _playerDir;
	std::pair<double, double> _pacManPos;
	int _lifes;
	clock_t myClock;
	clock_t _godModeStart;
	clock_t _godMode;
	double _ghostSpeed;
};

#endif // PACMAN_HPP_
