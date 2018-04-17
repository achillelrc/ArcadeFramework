//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// Nibbler.cpp
//

#include "Nibbler.hpp"
#include "Error.hpp"

extern "C" {
	void __attribute__((constructor)) calledFirst();
	void __attribute__((destructor)) calledLast();
	static IGameModule *myLib;

	void calledFirst()
	{
		myLib = new Nibbler;
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

NibblerTilemap::NibblerTilemap() : _path(RESOURCES_PATH + std::string("tilesnak.png")), _scale(20)
{
	_tilemap['a'] = std::make_pair(20, 20);
	_tilemap['A'] = std::make_pair(169, 1);
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
	_tilemap['O'] = std::make_pair(169, 274);
	_tilemap['1'] = std::make_pair(43, 64);
	_tilemap['2'] = std::make_pair(64, 64);
	_tilemap['3'] = std::make_pair(85, 85);
	_tilemap['4'] = std::make_pair(85, 64);
	_tilemap['5'] = std::make_pair(22, 64);
}

NibblerTilemap::~NibblerTilemap()
{
}

int NibblerTilemap::getScale() const
{
	return (this->_scale);
}

std::map<char, std::pair<int, int>> NibblerTilemap::getTilemap() const
{
	return (this->_tilemap);
}

std::string NibblerTilemap::getTilemapPath() const
{
	return (this->_path);
}

void Nibbler::initMap(const std::string &map)
{
	std::string line;
	std::fstream file;
	int cnt = 0;

	try {
		_gameMap.clear();
		file.open(RESOURCES_PATH + MAP_PATH + map);
		while (getline(file, line)) {
			for (size_t i = 0; i < line.size(); ++i)
				cnt = (line.at(i) == ' ') ? cnt + 1 : cnt;
			_gameMap.push_back(line);
		}
		_maxCells = cnt;
		file.close();
		if (_gameMap.empty())
			throw Handler("Nibbler", "cannot load map");
	}
	catch (Handler &e) {
		std::cerr << e.what();
		exit(84);
	}
}

Nibbler::NibblerDir_e Nibbler::calcDir()
{

	if (_pDir == _NibblerDir || (_pDir == UP_DIR && _NibblerDir == DOWN_DIR) || (_pDir == DOWN_DIR && _NibblerDir == UP_DIR) || (_pDir == LEFT_DIR && _NibblerDir == RIGHT_DIR) || (_pDir == RIGHT_DIR && _NibblerDir == LEFT_DIR))
		return (_NibblerDir);
	if (_pDir == UP_DIR && fabs(floor((float)_objMap[0].x)) == fabs((float)_objMap[0].x) && fabs(floor((float)_objMap[0].y)) == fabs((float)_objMap[0].y) &&
	    _gameMap[floor(_objMap[0].y - 0.1)][round(_objMap[0].x)] == ' ') {
		    return (UP_DIR);
	}
	if (_pDir == DOWN_DIR && fabs(floor((float)_objMap[0].x)) == fabs((float)_objMap[0].x) && fabs(floor((float)_objMap[0].y)) == fabs((float)_objMap[0].y) &&
	    _gameMap[ceil(_objMap[0].y + 0.1)][round(_objMap[0].x)] == ' ') {
		    return (DOWN_DIR);
	}
	if (_pDir == LEFT_DIR && fabs(floor((float)_objMap[0].x)) == fabs((float)_objMap[0].x) && fabs(floor((float)_objMap[0].y)) == fabs((float)_objMap[0].y) &&
	    _gameMap[round(_objMap[0].y)][floor(_objMap[0].x - 0.1)] == ' ') {
		    return (LEFT_DIR);
	}
	if (_pDir == RIGHT_DIR && fabs(floor((float)_objMap[0].x)) == fabs((float)_objMap[0].x) && fabs(floor((float)_objMap[0].y)) == fabs((float)_objMap[0].y) &&
	    _gameMap[round(_objMap[0].y)][ceil(_objMap[0].x + 0.1)] == ' ') {
		    return (RIGHT_DIR);
	}
	return (_NibblerDir);
}

void Nibbler::NibblerTick()
{
	static double xx = 0;
	static double yy = 0;

	if ((_NibblerDir == LEFT_DIR && _gameMap[round(_objMap[0].y)][floor(_objMap[0].x - 0.3)] != ' ') || (_NibblerDir == RIGHT_DIR && _gameMap[round(_objMap[0].y)][ceil(_objMap[0].x + 0.3)] != ' ') || (_NibblerDir == UP_DIR && _gameMap[floor(_objMap[0].y - 0.3)][round(_objMap[0].x)] != ' ') || (_NibblerDir == DOWN_DIR && _gameMap[ceil(_objMap[0].y + 0.3)][round(_objMap[0].x)] != ' ')) {
		if (_NibblerDir != LEFT_DIR && _NibblerDir != RIGHT_DIR && _gameMap[round(_objMap[0].y)][floor(_objMap[0].x - 0.4)] == ' ')
			_NibblerDir = (_pDir == RIGHT_DIR && _gameMap[round(_objMap[0].y)][ceil(_objMap[0].x + 0.4)] == ' ') ? RIGHT_DIR : LEFT_DIR;
		else if (_NibblerDir != RIGHT_DIR && _NibblerDir != LEFT_DIR && _gameMap[round(_objMap[0].y)][ceil(_objMap[0].x + 0.4)] == ' ')
			_NibblerDir = RIGHT_DIR;
		else if (_NibblerDir != UP_DIR && _NibblerDir != DOWN_DIR && _gameMap[floor(_objMap[0].y - 0.4)][round(_objMap[0].x)] == ' ')
			_NibblerDir = (_pDir == DOWN_DIR && _gameMap[ceil(_objMap[0].y + 0.4)][round(_objMap[0].x)] == ' ') ? DOWN_DIR : UP_DIR;
		else if (_NibblerDir != UP_DIR && _NibblerDir != DOWN_DIR && _gameMap[ceil(_objMap[0].y + 0.4)][round(_objMap[0].x)] == ' ')
			_NibblerDir = DOWN_DIR;
		if (_pDir != _NibblerDir && ((round(0) == round(_objMap[0].x - 1) && (_pDir == LEFT_DIR || _pDir == RIGHT_DIR)) || (round(0) == round(_objMap[0].y - 1) && (_pDir == DOWN_DIR || _pDir == UP_DIR)) || (round(_mapSize.first - 1) == round(_objMap[0].x + 1) && (_pDir == LEFT_DIR || _pDir == RIGHT_DIR)) || (round(_mapSize.second - 1) == round(_objMap[0].y + 1) && (_pDir == DOWN_DIR || _pDir == UP_DIR)))) {
			this->saveScore();
			this->_score = 0;
			this->init();
			this->_graphicModule->printText("GAME OVER", 1000000);
			this->_graphicModule->printText("READY", 1000000);
			return;
		}
		_pDir = _NibblerDir;
	}
	_NibblerDir = calcDir();
	if (_NibblerDir == UP_DIR && _gameMap[floor(_objMap[0].y - 0.1)][round(_objMap[0].x)] == ' ')
		_objMap[0].y -= 0.1;
	else if (_NibblerDir == DOWN_DIR && _gameMap[ceil(_objMap[0].y + 0.1)][round(_objMap[0].x)] == ' ')
		_objMap[0].y += 0.1;
	else if (_NibblerDir == DOWN_DIR || _NibblerDir == UP_DIR)
		_NibblerDir = _pDir;

	if (_NibblerDir == LEFT_DIR && _gameMap[round(_objMap[0].y)][floor(_objMap[0].x - 0.1)] == ' ')
		_objMap[0].x -= 0.1;
	else if (_NibblerDir == RIGHT_DIR && _gameMap[round(_objMap[0].y)][ceil(_objMap[0].x + 0.1)] == ' ')
		_objMap[0].x += 0.1;
	else if (_NibblerDir == LEFT_DIR || _NibblerDir == RIGHT_DIR)
		_NibblerDir = _pDir;
	if (xx == _objMap[0].x)
		_objMap[0].x = round(_objMap[0].x);
	if (yy == _objMap[0].y)
		_objMap[0].y = round(_objMap[0].y);
	xx = _objMap[0].x;
	yy = _objMap[0].y;
}

void Nibbler::updateTail()
{
	for (size_t i = 1; i < _objMap.size(); ++i) {
		if (_objMap.size() - 1 >= (unsigned)_maxCells || (i > 3 && round(_objMap[0].x) == round(_objMap[i].x) && round(_objMap[0].y) == round(_objMap[i].y))) {
			this->saveScore();
			this->_score = 0;
			this->init();
			this->_graphicModule->printText("GAME OVER", 1000000);
			this->_graphicModule->printText("READY", 1000000);
			return;
		}
		_objMap[i].x = _TailsPos.at(i - 1).at(9).x;
		_objMap[i].y = _TailsPos.at(i - 1).at(9).y;
		_TailsPos.at(i).insert(_TailsPos.at(i).begin(), {_objMap[i].x, _objMap[i].y, 0, ""});
		_TailsPos.at(i).erase(_TailsPos.at(i).begin() + 10);
	}
	_TailsPos.at(0).insert(_TailsPos.at(0).begin(), {_objMap[0].x, _objMap[0].y, 0, ""});
	_TailsPos.at(0).erase(_TailsPos.at(0).begin() + 10);
	for (size_t i = 0; i < _foodMap.size(); ++i) {
		if (round(_objMap[0].x) == round(_foodMap[i].x) && round(_objMap[0].y) == round(_foodMap[i].y)) {
			_foodMap.erase(_foodMap.begin() + i);
			_objMap.push_back(_objMap[_objMap.size() - 1]);
			_TailsPos.push_back(_TailsPos.at(_TailsPos.size() - 1));
			_score += 10 + 5 * _objMap.size();
			break;
		}
	}
}

Nibbler::Nibbler() :  _tilemap(new NibblerTilemap), _state(0), _name("Nibbler"), _score(0), _mapSize(std::make_pair(19.0, 19.0)), _NibblerDir(NONE_DIR)
{
	init();
}

Nibbler::~Nibbler()
{
}

void Nibbler::setGraphicalLib(IDisplayModule *graphicModule)
{
	this->_graphicModule = graphicModule;
}

void Nibbler::init()
{
	objPos_t emptyOne;

	if (!this->_score)
		initMap(NIBL_LVL1);
	else if (this->_score > 300 && this->_score < 600)
		initMap(NIBL_LVL2);
	else if (this->_score >= 600)
		initMap(NIBL_LVL3);
	srand(time(NULL));
	this->_objMap.clear();
	this->_TailsPos.clear();
	this->_foodMap.clear();
	for (int i = 4; i > 0; --i)
		this->_objMap.push_back({9.0, 15.0 - i, (i == 0) ? '3' : '5', "Nibbler"});
	std::vector<objPos_t> tmp;
	for (int i = 0; i < 4; ++i) {
		tmp.clear();
		for (int j = 0; j < 10; ++j)
			tmp.push_back({9.0, 11.0 + 0.1 * j, 0, ""});
		this->_TailsPos.push_back(tmp);
	}
	_pDir = UP_DIR;
	_NibblerDir = UP_DIR;
}

const std::string &Nibbler::getName() const
{
	return (_name);
}

void Nibbler::setHandler(void *handler)
{
	this->_handler = handler;
}

void Nibbler::updateFood()
{
	int x = floor(_mapSize.first);
	int y = floor(_mapSize.second);

	if (_foodMap.size() == 0)
		for (int i = 0; i < 2; ++i) {
			int xx = 0;
			int yy = 0;
			while (42) {
				xx = rand() % x;
				yy = rand() % y;
				size_t u = 0;
				for (; u < _objMap.size() && round(xx) != round(_objMap[u].x) && round(yy) != round(_objMap[u].y); ++u);
				if (u != _objMap.size() && _gameMap[yy][xx] == ' ')
					break;
			}
			_foodMap.push_back({(double)xx, (double)yy, 'A', "food"});
		}
}

int Nibbler::runGame()
{
	static int prevscor = this->_score;

	this->_graphicModule->printText("READY", 500000);
	this->_graphicModule->updateDisplay(this);
	this->_state = 1;
	while (this->_state == 1) {
		NibblerTick();
		updateFood();
		updateTail();
		this->keyAction(this->_graphicModule->getKey());
		if (this->_state != 1)
		return (this->_state);
		this->_objMap[0].value = _NibblerDir + 48;
		this->_graphicModule->updateDisplay(this);
		if ((prevscor < 300 && this->_score >= 300) || (prevscor < 600 && this->_score >= 600))
			init();
		prevscor = this->_score;
		usleep(15000);
	}
	return (0);
}

void Nibbler::keyAction(std::string key)
{
	if (key == NEXT_GAME_KEY) {
		saveScore();
		this->_score = 0;
		this->_state = 2;
	}
	if (key == PREV_GAME_KEY) {
		saveScore();
		this->_score = 0;
		this->_state = 2;
	}
	if (key == MENU_KEY) {
		saveScore();
		this->_score = 0;
		this->_state = 0;
	}
	if (key == RESTART_GAME_KEY) {
		saveScore();
		this->_graphicModule->printText("RESTART", 1000000);
		this->_graphicModule->printText("READY", 1000000);
		this->_score = 0;
		init();
	}
	if (key == RIGHT_KEY)
		this->_pDir = RIGHT_DIR;
	if (key == LEFT_KEY)
		this->_pDir = LEFT_DIR;
	if (key == UP_KEY)
		this->_pDir = UP_DIR;
	if (key == DOWN_KEY)
		this->_pDir = DOWN_DIR;
}

const std::vector<std::string> Nibbler::getGameMap() const
{
	return (this->_gameMap);
}

const std::vector<objPos_t> Nibbler::getObjPos() const
{
	std::vector<objPos_t> all = this->_objMap;
	for (size_t i = 0; i < _foodMap.size(); ++i)
		all.push_back(_foodMap[i]);
	return (all);
}

int Nibbler::getScore() const
{
	return (this->_score);
}

ITilemap *Nibbler::getTilemap() const
{
	return (this->_tilemap);
}

std::string Nibbler::getUserName() const
{
	return (this->_graphicModule->getUserName());
}

void Nibbler::saveScore() const
{
	std::ofstream myfile;
	std::string scorePath = SCORE_PATH + this->getName();

	myfile.open(scorePath, std::ios::out | std::ios::app | std::ios::binary);
	if (this->getScore())
	myfile << this->getUserName() << " : " << this->getScore() << "\n";
	myfile.close();
}

void *Nibbler::getHandler() const
{
	return (this->_handler);
}

std::pair<double, double> Nibbler::getMapSize() const
{
	return (this->_mapSize);
}
