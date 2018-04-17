//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// PacMan.cpp
//

#include "PacMan.hpp"
#include "Paths.hpp"
#include "Error.hpp"
#include <string.h>
#include <unistd.h>
#include <fstream>
#include "DefaultKeys.hpp"
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

extern "C" {
	void __attribute__((constructor)) calledFirst();
	void __attribute__((destructor)) calledLast();
	static IGameModule *myLib;

	void calledFirst()
	{
		myLib = new PacMan;
	}

	void calledLast()
	{
		delete myLib;
	}

	IGameModule *GameEntryPoint()
	{
		return (myLib);
	}
}

PacManTilemap::PacManTilemap() : _path(RESOURCES_PATH + std::string("tileset.png")), _scale(20)
{
	_tilemap[0] = std::make_pair(0, 0);
	_tilemap['b'] = std::make_pair(127, 211);
	_tilemap['_'] = std::make_pair(148, 274);
	_tilemap['|'] = std::make_pair(127, 274);
	_tilemap['d'] = std::make_pair(169, 211);
	_tilemap['q'] = std::make_pair(127, 253);
	_tilemap['p'] = std::make_pair(169, 253);
	_tilemap['T'] = std::make_pair(148, 211);
	_tilemap['t'] = std::make_pair(148, 253);
	_tilemap['u'] = std::make_pair(211, 253);
	_tilemap['U'] = std::make_pair(190, 253);
	_tilemap['-'] = std::make_pair(190, 274);
	_tilemap['='] = std::make_pair(211, 274);
	_tilemap['K'] = std::make_pair(127, 232);
	_tilemap['k'] = std::make_pair(169, 232);
	_tilemap['L'] = std::make_pair(274, 64);
	_tilemap['C'] = std::make_pair(64, 85);
	_tilemap['c'] = std::make_pair(1, 64);
	_tilemap['v'] = std::make_pair(1, 127);
	_tilemap['V'] = std::make_pair(1, 107);
	_tilemap['s'] = std::make_pair(106, 106);
	_tilemap['.'] = std::make_pair(253, 1);
	_tilemap['*'] = std::make_pair(273, 1);
	_tilemap['f'] = std::make_pair(85, 22);
	_tilemap['F'] = std::make_pair(106, 22);
	_tilemap['g'] = std::make_pair(127, 22);
	_tilemap['G'] = std::make_pair(148, 22);
	_tilemap['i'] = std::make_pair(169, 43);
	_tilemap['I'] = std::make_pair(190, 43);
	_tilemap['y'] = std::make_pair(211, 43);
	_tilemap['Y'] = std::make_pair(232, 43);
	_tilemap['e'] = std::make_pair(1, 43);
	_tilemap['E'] = std::make_pair(22, 43);
	_tilemap['j'] = std::make_pair(43, 43);
	_tilemap['J'] = std::make_pair(64, 43);
	_tilemap['1'] = std::make_pair(85, 43);
	_tilemap['2'] = std::make_pair(106, 43);
	_tilemap['3'] = std::make_pair(127, 43);
	_tilemap['4'] = std::make_pair(148, 43);
	_tilemap['5'] = std::make_pair(1, 22);
	_tilemap['6'] = std::make_pair(22, 22);
	_tilemap['7'] = std::make_pair(43, 22);
	_tilemap['8'] = std::make_pair(64, 22);
}

PacManTilemap::~PacManTilemap()
{
}

int PacManTilemap::getScale() const
{
	return (this->_scale);
}

std::map<char, std::pair<int, int>> PacManTilemap::getTilemap() const
{
	return (this->_tilemap);
}

std::string PacManTilemap::getTilemapPath() const
{
	return (this->_path);
}

void PacMan::initMap()
{
	std::string line;
	std::fstream file;
	std::string fileName;

	try {
		_gameMap.clear();
		fileName = RESOURCES_PATH + MAP_PATH + "pacmanmap";
		file.open(fileName);
		while (getline(file, line)) {
			_gameMap.push_back(line);
		}
		if (_gameMap.empty())
			throw Handler("PacMan", "cannot load map");
		file.close();
	}
	catch (Handler &e) {
		std::cerr << e.what();
		exit(84);
	}
}

void PacMan::moveUp()
{
	this->_playerDir = UP_DIR;
}

void PacMan::moveDown()
{
	this->_playerDir = DOWN_DIR;
}

void PacMan::moveLeft()
{
	this->_playerDir = LEFT_DIR;
}

void PacMan::moveRight()
{
	this->_playerDir = RIGHT_DIR;
}

bool isWalkable(char pos)
{
	if (pos == ' ')
		return (1);
	if (pos == '*')
		return (1);
	if (pos == '.')
		return (1);
	return (0);
}

bool isBlacklisted(int x, int y)
{
	if (y == 11 && x == 9)
		return (1);
	if (y == 9 && x == 0)
		return (1);
	if (y == 9 && x == 18)
		return (1);
	if (x == 9 && y == 9)
		return (1);
	if (x == 9 && y == 8)
		return (1);
	if (x == 10 && y == 9)
		return (1);
	if (x == 8 && y == 9)
		return (1);
	if (x == 17 && y == 17)
		return (1);
	if (x == 1 && y == 17)
		return (1);
	if (x == 17 && y == 1)
		return (1);
	if (x == 1 && y == 1)
		return (1);
	return (0);
}

bool isSuperPacGum(int x, int y)
{
	if (x == 17 && y == 17)
		return (1);
	if (x == 1 && y == 17)
		return (1);
	if (x == 17 && y == 1)
		return (1);
	if (x == 1 && y == 1)
		return (1);
	return (0);
}

bool PacMan::canWalkThroughLock(int x, int y)
{
	if (x == _objMap[1].x && y == _objMap[1].y) {
		if (_objMap[1].value == ' ')
			return (1);
		return (0);
	}
	return (1);
}

void PacMan::loadPacGums()
{
	int i = 0;
	int j = 0;
	int count = 0;

	this->_pacGums.clear();
	while (i < _mapSize.first) {
		j = 0;
		while (j < _mapSize.second) {
			if (isWalkable(_gameMap[i][j]) && !isBlacklisted(j, i)) {
				objPos_t pacGum;
				pacGum.x = j;
				pacGum.y = i;
				pacGum.value = '.';
				pacGum.name = "pacGum";
				count = count + 1;
				_pacGums.push_back(pacGum);
			}
			else if (isSuperPacGum(j, i)) {
				objPos_t superPacGum;
				superPacGum.x = j;
				superPacGum.y = i;
				superPacGum.value = '*';
				superPacGum.name = "Super PacGum";
				_pacGums.push_back(superPacGum);
			}
			j++;
		}
		i++;
	}
}

void PacMan::initGhosts()
{
	this->_ghosts.clear();
	this->_ghostsDir.clear();
	this->_ghosts.push_back({10, 9, '1', "GHOST_A"});
	this->_ghostsDir.push_back(LEFT_DIR);
	this->_ghosts.push_back({9, 9, '1', "GHOST_B"});
	this->_ghostsDir.push_back(RIGHT_DIR);
	this->_ghosts.push_back({8, 9, '1', "GHOST_C"});
	this->_ghostsDir.push_back(RIGHT_DIR);
	this->_ghosts.push_back({9, 9, '1', "GHOST_D"});
	this->_ghostsDir.push_back(LEFT_DIR);
}

void PacMan::checkGodMode()
{
	if (_godMode && (((float)clock() - _godModeStart)/CLOCKS_PER_SEC) >= 5.0) {
		_godMode = 0;
		_godModeStart = 0;
		_ghostSpeed = 0.1;
	}
}

void PacMan::eatPacGum()
{
	unsigned int i = 0;
	std::map<std::pair<double, double>, int> counter;

	while (i < _pacGums.size()) {
		if (round(_pacManPos.second) == round(_pacGums[i].y)
		&& round(_pacManPos.first) == round(_pacGums[i].x)
		 && _pacGums[i].value == '.') {
			_pacGums[i].value = ' ';
			_score += 100;
		}
		else if (round(_pacManPos.second) == round(_pacGums[i].y)
		&& round(_pacManPos.first) == round(_pacGums[i].x)
		&& _pacGums[i].value == '*') {
			_pacGums[i].value = ' ';
			_score += 1000;
			_godModeStart = clock();
			_godMode = 1;
			_ghostSpeed = 0.05;
		}
		i++;
	}
}

bool PacMan::checkForWin()
{
	unsigned int i = 0;

	while (i < _pacGums.size()) {
		if (_pacGums[i].value == '.' || _pacGums[i].value == '*')
		return (0);
		i++;
	}
	return (1);
}

char getTileFromDir(PacMan::PacManDirection_e dir)
{
	switch (dir) {
		case PacMan::NONE_DIR:
		return ('v');
		break;
		case PacMan::UP_DIR:
		return ('v');
		break;
		case PacMan::DOWN_DIR:
		return ('V');
		break;
		case PacMan::LEFT_DIR:
		return ('c');
		break;
		case PacMan::RIGHT_DIR:
		return ('C');
		break;
	}
	return ('?');
}

char weakGhostTile(PacMan::PacManDirection_e dir)
{
	switch (dir) {
		case PacMan::NONE_DIR:
		return ('7');
		break;
		case PacMan::UP_DIR:
		return ('8');
		break;
		case PacMan::DOWN_DIR:
		return ('7');
		break;
		case PacMan::LEFT_DIR:
		return ('5');
		break;
		case PacMan::RIGHT_DIR:
		return ('6');
		break;
	}
	return ('?');
}

char getGhostTileFromDir(int i, PacMan::PacManDirection_e dir)
{
	switch (i) {
		case 0:
		switch (dir) {
			case PacMan::NONE_DIR:
			return ('g');
			break;
			case PacMan::UP_DIR:
			return ('G');
			break;
			case PacMan::DOWN_DIR:
			return ('g');
			break;
			case PacMan::LEFT_DIR:
			return ('f');
			break;
			case PacMan::RIGHT_DIR:
			return ('F');
			break;
		}
		break;
		case 1:
		switch (dir) {
			case PacMan::NONE_DIR:
			return ('y');
			break;
			case PacMan::UP_DIR:
			return ('Y');
			break;
			case PacMan::DOWN_DIR:
			return ('y');
			break;
			case PacMan::LEFT_DIR:
			return ('i');
			break;
			case PacMan::RIGHT_DIR:
			return ('I');
			break;
		}
		break;
		case 2:
		switch (dir) {
			case PacMan::NONE_DIR:
			return ('j');
			break;
			case PacMan::UP_DIR:
			return ('J');
			break;
			case PacMan::DOWN_DIR:
			return ('j');
			break;
			case PacMan::LEFT_DIR:
			return ('e');
			break;
			case PacMan::RIGHT_DIR:
			return ('E');
			break;
		}
		break;
		case 3:
		switch (dir) {
			case PacMan::NONE_DIR:
			return ('3');
			break;
			case PacMan::UP_DIR:
			return ('4');
			break;
			case PacMan::DOWN_DIR:
			return ('3');
			break;
			case PacMan::LEFT_DIR:
			return ('1');
			break;
			case PacMan::RIGHT_DIR:
			return ('2');
			break;
		}
		break;
	}
	return ('?');
}

std::vector<PacMan::PacManDirection_e> PacMan::calcAllDir(objPos_t ghost, PacMan::PacManDirection_e oldDir)
{
	std::vector<PacMan::PacManDirection_e> dirs;

	if (fabs(floor((float)ghost.x)) == fabs((float)ghost.x)
	&& fabs(floor((float)ghost.y)) == fabs((float)ghost.y)
	&& _gameMap[floor(ghost.y - _ghostSpeed)][round(ghost.x)] == ' ') {
		dirs.push_back(PacMan::UP_DIR);
	}
	if (fabs(floor((float)ghost.x)) == fabs((float)ghost.x)
	&& fabs(floor((float)ghost.y)) == fabs((float)ghost.y)
	&& _gameMap[ceil(ghost.y + _ghostSpeed)][round(ghost.x)] == ' ') {
		dirs.push_back(PacMan::DOWN_DIR);
	}
	if (fabs(floor((float)ghost.x)) == fabs((float)ghost.x)
	&& fabs(floor((float)ghost.y)) == fabs((float)ghost.y)
	&& _gameMap[round(ghost.y)][floor(ghost.x - _ghostSpeed)] == ' ') {
		dirs.push_back(PacMan::LEFT_DIR);
	}
	if (fabs(floor((float)ghost.x)) == fabs((float)ghost.x)
	&& fabs(floor((float)ghost.y)) == fabs((float)ghost.y)
	&& _gameMap[round(ghost.y)][ceil(ghost.x + _ghostSpeed)] == ' ') {
		dirs.push_back(PacMan::RIGHT_DIR);
	}
	if (dirs.empty()) {
		dirs.push_back(oldDir);
	}
	return (dirs);
}

PacMan::PacManDirection_e PacMan::calcDir()
{
	if (_playerDir == UP_DIR
		&& fabs(floor((float)_objMap[0].x)) == fabs((float)_objMap[0].x)
		&& fabs(floor((float)_objMap[0].y)) == fabs((float)_objMap[0].y)
		&& _gameMap[floor(_objMap[0].y - 0.1)][round(_objMap[0].x)] == ' ') {
		return (UP_DIR);
	}
	if (_playerDir == DOWN_DIR
		&& fabs(floor((float)_objMap[0].x)) == fabs((float)_objMap[0].x)
		&& fabs(floor((float)_objMap[0].y)) == fabs((float)_objMap[0].y)
		&& _gameMap[ceil(_objMap[0].y + 0.1)][round(_objMap[0].x)] == ' ') {
		return (DOWN_DIR);
	}
	if (_playerDir == LEFT_DIR
		&& fabs(floor((float)_objMap[0].x)) == fabs((float)_objMap[0].x)
		&& fabs(floor((float)_objMap[0].y)) == fabs((float)_objMap[0].y)
		&& _gameMap[round(_objMap[0].y)][floor(_objMap[0].x - 0.1)] == ' ') {
		return (LEFT_DIR);
	}
	if (_playerDir == RIGHT_DIR
		&& fabs(floor((float)_objMap[0].x)) == fabs((float)_objMap[0].x)
		&& fabs(floor((float)_objMap[0].y)) == fabs((float)_objMap[0].y)
		&& _gameMap[round(_objMap[0].y)][ceil(_objMap[0].x + 0.1)] == ' ') {
		return (RIGHT_DIR);
	}
	return (_pacManDir);
}

int PacMan::ghostTick(int i, objPos_t &ghost, PacMan::PacManDirection_e dir)
{
	static std::map<std::string, std::pair<double, double>> oldPos;
	double x = ghost.x;
	double y = ghost.y;

	if (dir == LEFT_DIR && round(x) == 0 && round(y) == 9) {
		x = 18;
	}
	else if (dir == RIGHT_DIR && round(x) == 18 && round(y) == 9) {
		x = 0;
	}
	if (dir == UP_DIR && isWalkable(_gameMap[floor(y - _ghostSpeed)][round(x)]))
	y -= _ghostSpeed;
	else if (dir == DOWN_DIR && isWalkable(_gameMap[ceil(y + _ghostSpeed)][round(x)]))
	y += _ghostSpeed;
	if (dir == LEFT_DIR && isWalkable(_gameMap[round(y)][floor(x - _ghostSpeed)]))
		x -= _ghostSpeed;
	else if (dir == RIGHT_DIR && isWalkable(_gameMap[round(y)][ceil(x + _ghostSpeed)]))
	x += _ghostSpeed;
	if (oldPos[ghost.name].first == x)
	x = round(x);
	if (oldPos[ghost.name].second == y)
	y = round(y);
	oldPos[ghost.name] = std::make_pair((double)x, (double)y);
	if (!_godMode)
	ghost.value = getGhostTileFromDir(i, dir);
	else
	ghost.value = weakGhostTile(dir);
	ghost.x = x;
	ghost.y = y;
	return (0);
}

PacMan::PacManDirection_e OpositeDir(PacMan::PacManDirection_e dir)
{
	switch (dir) {
		case PacMan::NONE_DIR:
		return (PacMan::NONE_DIR);
		break;
		case PacMan::UP_DIR:
		return (PacMan::DOWN_DIR);
		break;
		case PacMan::DOWN_DIR:
		return (PacMan::UP_DIR);
		break;
		case PacMan::LEFT_DIR:
		return (PacMan::RIGHT_DIR);
		break;
		case PacMan::RIGHT_DIR:
		return (PacMan::LEFT_DIR);
		break;
	}
	return (dir);
}

void PacMan::moveGhosts()
{
	unsigned int i = 0;

	while (i < _ghosts.size()) {
		std::vector<PacMan::PacManDirection_e> dirs = calcAllDir(_ghosts[i], _ghostsDir[i]);
		PacMan::PacManDirection_e newDir = dirs[(int)rand() % dirs.size()];
		int trys = 0;

		while (trys < 11 && newDir == OpositeDir(_ghostsDir[i])) {
			newDir = dirs[(int)(rand() % dirs.size())];
			trys++;
		}
		_ghostsDir[i] = newDir;
		ghostTick(i, _ghosts[i], newDir);
		i++;
	}
}

void PacMan::pacManTick()
{
	_pacManDir = calcDir();
	static double xx = 0;
	static double yy = 0;

	double x = _pacManPos.first;
	double y = _pacManPos.second;

	if (_pacManDir == LEFT_DIR && round(x) == 0 && round(y) == 9) {
		x = 18;
	}
	else if (_pacManDir == RIGHT_DIR && round(x) == 18 && round(y) == 9) {
		x = 0;
	}
	if (_pacManDir == UP_DIR && isWalkable(_gameMap[floor(y - 0.1)][round(x)]))
	y -= 0.1;
	else if (_pacManDir == DOWN_DIR && isWalkable(_gameMap[ceil(y + 0.1)][round(x)]))
	y += 0.1;
	else if (_pacManDir == DOWN_DIR || _pacManDir == UP_DIR)
		_pacManDir = _playerDir;
	if (_pacManDir == LEFT_DIR && isWalkable(_gameMap[round(y)][floor(x - 0.1)]))
		x -= 0.1;
	else if (_pacManDir == RIGHT_DIR && isWalkable(_gameMap[round(y)][ceil(x + 0.1)]))
	x += 0.1;
	else if (_pacManDir == LEFT_DIR || _pacManDir == RIGHT_DIR)
	_pacManDir = _playerDir;
	if (xx == x)
	x = round(x);
	if (yy == y)
	y = round(y);
	xx = x;
	yy = y;
	_pacManPos.first = x;
	_pacManPos.second = y;
	_objMap[0].value = getTileFromDir(_pacManDir);
	_objMap[0].x = _pacManPos.first;
	_objMap[0].y = _pacManPos.second;
}

PacMan::PacMan() :  _tilemap(new PacManTilemap), _state(0), _name("PacMan"), _score(0), _mapSize(std::make_pair(19.0, 19.0)), _pacManDir(NONE_DIR), _pacManPos(std::make_pair<double, double>(9.0, 11.0)), _lifes(3)
{
	init();
}

PacMan::~PacMan()
{
}

void PacMan::setGraphicalLib(IDisplayModule *graphicModule)
{
	this->_graphicModule = graphicModule;
}

void PacMan::init()
{
	objPos_t emptyOne;

	srand(time(NULL));
	initMap();
	this->_objMap.clear();
	this->_objMap.push_back({9, 11, 'c', "PacMan"});
	this->_objMap.push_back({9, 8, 'L', "Lock"});
	_state = 1;
	_score = 0;
	_lifes = 3;
	_godMode = 0;
	_godModeStart = 0;
	_ghostSpeed = 0.1;
	_pacManDir = NONE_DIR;
	_playerDir = NONE_DIR;
	_pacManPos.first = _objMap[0].x;
	_pacManPos.second = _objMap[0].y;
	loadPacGums();
	initGhosts();
	ghostLock(1);
	myClock = clock();
}

const std::string &PacMan::getName() const
{
	return (_name);
}

void PacMan::setHandler(void *handler)
{
	this->_handler = handler;
}

bool isLockedGhost(objPos_t ghost)
{
	if ((ghost.x >= 8.0 && ghost.x <= 10.0) && round(ghost.y) == 9.0) {
		return (1);
	}
	return (0);
}

unsigned int nbLockedGhosts(std::vector<objPos_t> ghosts)
{
	unsigned int i = 0;
	unsigned int count = 0;

	while (i < ghosts.size()) {
		if (isLockedGhost(ghosts[i]))
		count += 1;
		i++;
	}
	return (count);
}

void PacMan::ghostLock(bool reset)
{
	static clock_t timeOpen = 0;
	static unsigned int prevGhostNb = 4;
	int myTime;
	int myTimeOpen;

	if (reset) {
		timeOpen = 0;
		prevGhostNb = 4;
		return;
	}
	myTime = (((float)clock() - myClock)/CLOCKS_PER_SEC);
	myTimeOpen = (((float)clock() - timeOpen)/CLOCKS_PER_SEC) * 1000;
	if (nbLockedGhosts(_ghosts) > 0 && myTime >= 5) {
		myClock = clock();
		timeOpen = clock();
		prevGhostNb = nbLockedGhosts(_ghosts);
		_gameMap[8][9] = ' ';
	}
	else if (myTimeOpen > 375 && nbLockedGhosts(_ghosts) < prevGhostNb) {
		_gameMap[8][9] = 'L';
		timeOpen = 0;
	}
}

void PacMan::keyAction(std::string key)
{
	if (key == NEXT_GAME_KEY) {
		saveScore();
		this->_state = 2;
	}
	if (key == PREV_GAME_KEY) {
		saveScore();
		this->_state = 2;
	}
	if (key == MENU_KEY) {
		saveScore();
		this->_state = 0;
	}
	if (key == RESTART_GAME_KEY) {
		saveScore();
		init();
	}
	if (key == RIGHT_KEY)
	moveRight();
	if (key == LEFT_KEY)
	moveLeft();
	if (key == UP_KEY)
	moveUp();
	if (key == DOWN_KEY)
	moveDown();
}

const std::vector<std::string> PacMan::getGameMap() const
{
	return (this->_gameMap);
}

const std::vector<objPos_t> PacMan::getObjPos() const
{
	std::vector<objPos_t> concatVect;

	concatVect.insert(concatVect.end(), _pacGums.begin(), _pacGums.end());
	concatVect.insert(concatVect.end(), _ghosts.begin(), _ghosts.end());
	concatVect.insert(concatVect.end(), _objMap.begin(), _objMap.end());
	return (concatVect);
}

int PacMan::getScore() const
{
	return (this->_score);
}

ITilemap *PacMan::getTilemap() const
{
	return (this->_tilemap);
}

std::string PacMan::getUserName() const
{
	return (this->_graphicModule->getUserName());
}

int PacMan::detectGhostCollide()
{
	unsigned int i = 0;

	while (i < _ghosts.size()) {
		if (round(_pacManPos.second) == round(_ghosts[i].y) && round(_pacManPos.first) == round(_ghosts[i].x)) {
			if (!_godMode)
			{
				_lifes -= 1;
				if (_lifes <= 0) {
					this->saveScore();
					this->_graphicModule->printText("Game Over");
					this->_state = 3;
				}
				else {
					this->_graphicModule->printText("Lifes : " + std::to_string(_lifes), 1000000);
					_pacManPos.first = 9;
					_pacManPos.second = 11;
					_pacManDir = NONE_DIR;
					_playerDir = NONE_DIR;
					ghostLock(1);
					initGhosts();
					myClock = clock();
				}

				this->_graphicModule->printText("Ready !");
			}
			else
			{
				_score += 1000;
				_ghosts[i].x = 8;
				_ghosts[i].y = 9;
				_ghostsDir[i] = NONE_DIR;
			}
		}
		i++;
	}
	return (0);
}

void PacMan::saveScore() const
{
	std::ofstream myfile;
	std::string scorePath = SCORE_PATH + this->getName();

	myfile.open(scorePath, std::ios::out | std::ios::app | std::ios::binary);
	if (this->getScore())
	myfile << this->getUserName() << " : " << this->getScore() << "\n";
	myfile.close();
}

void *PacMan::getHandler() const
{
	return (this->_handler);
}

std::pair<double, double> PacMan::getMapSize() const
{
	return (this->_mapSize);
}

int PacMan::runGame()
{
	this->_state = 1;
	this->_graphicModule->printText("Ready !");
	myClock = clock();
	while (this->_state == 1) {
		this->_graphicModule->updateDisplay(this);
		this->keyAction(this->_graphicModule->getKey());
		if (this->_state != 1)
		return (this->_state);
		pacManTick();
		moveGhosts();
		detectGhostCollide();
		eatPacGum();
		ghostLock();
		checkGodMode();
		if (checkForWin()) {
			int score = _score;
			init();
			this->_graphicModule->printText("Ready !");
			_score = score;
		}
		usleep(15000);
	}
	return (this->_state);
}
