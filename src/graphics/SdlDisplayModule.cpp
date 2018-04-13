//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// SdlDisplayModule.cpp
//

#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Paths.hpp"
#include "SdlDisplayModule.hpp"
#include "ITilemap.hpp"
#include "DefaultKeys.hpp"

extern "C" {
	void __attribute__((constructor)) calledFirst();
	void __attribute__((destructor)) calledLast();
	static SdlDisplayModule *myLib;

	void calledFirst()
	{
		myLib = new SdlDisplayModule;
	}

	void calledLast()
	{
		delete myLib;
	}

	IDisplayModule *LibEntryPoint()
	{
		return (myLib);
	}
}

void SdlDisplayModule::genSprite(std::string name, const char *path, const char *msg)
{
	SDL_Surface *surf;

	if (msg) {
		TTF_Font *font = TTF_OpenFont(path, 35);
		if (!font)
		throw Handler("SDL2 lib", "ttf file load exception");
		SDL_Color tmpCol;
		tmpCol.r = 0xFF;
		tmpCol.g = 0xFF;
		tmpCol.b = 0xFF;
		surf = TTF_RenderText_Solid(font, msg, tmpCol);
		if (!surf)
		throw Handler("SDL2 lib", "rendering exception");
	}
	else {
		surf = IMG_Load(path);
		if (!surf)
		throw Handler("SDL2 lib", "surface file load exception");
		SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0, 0xFF, 0xFF));
	}
	boxes[name] = SDL_CreateTextureFromSurface(render, surf);
	if (!boxes[name])
	throw Handler("SDL2 lib", "rendering exception");
	SDL_FreeSurface(surf);
}

SdlDisplayModule::SdlDisplayModule() : menuMode(0), _name("SDL2.0Lib"), _userName("unknown")
{
}

void SdlDisplayModule::setGraphicLibName(std::vector<std::string> graphicLibName)
{
	this->_graphicLibName = graphicLibName;
}

void SdlDisplayModule::setGameLibName(std::vector<std::string> gameLibName)
{
	this->_gameLibName = gameLibName;
}

void SdlDisplayModule::setScore(std::vector<std::string> scores)
{
	this->_scores = scores;
}

void SdlDisplayModule::init(ICoreProgram *coreProgram)
{
	this->_coreProgram = coreProgram;
	if (SDL_Init(SDL_INIT_VIDEO) ||
	!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	throw Handler("SDL2 lib", "rendering exception");
	this->win = SDL_CreateWindow("arcade emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (!(this->win))
	throw Handler("SDL2 lib", "rendering exception");
	this->render = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!(this->render))
	throw Handler("SDL2 lib", "rendering exception");
	SDL_SetRenderDrawColor(this->render, 0xFF, 0xFF, 0xFF, 0xFF);
	if ((!IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG)
	throw Handler("SDL2 lib", "rendering exception");
	if (TTF_Init() == -1)
	throw Handler("SDL2 lib", "rendering exception");
	initMenu();
}

void SdlDisplayModule::destroy()
{
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(win);
	render = NULL;
	win = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SdlDisplayModule::printObjs(IGameModule *data, ITilemap *tmap)
{
	char tile = 0;
	SDL_Rect *zone;
	SDL_Rect *clip;
	int xx = 640 / 2 - data->getMapSize().first * tmap->getScale() / 2;
	std::vector<objPos_t> objMap = data->getObjPos();
	std::map<char, std::pair<int, int>> posmap = tmap->getTilemap();

	for (int x = objMap.size() - 1; x >= 0; --x) {
		tile = objMap[x].value;
		zone = new SDL_Rect{(int)(xx + objMap[x].x * tmap->getScale()), (int)(objMap[x].y * tmap->getScale()), tmap->getScale(), tmap->getScale()};
		clip = new SDL_Rect{posmap[tile].first + 1, posmap[tile].second + 1, tmap->getScale() - 1, tmap->getScale() - 2};
		if (SDL_RenderCopy(render, boxes["map"], clip, zone))
			throw Handler("SDL2 lib", "objs rendering exception");
	}
}

void SdlDisplayModule::printMap(IGameModule *data, ITilemap *tmap)
{
	SDL_Rect *zone;
	SDL_Rect *clip;
	int xx = 640 / 2 - data->getMapSize().first * tmap->getScale() / 2;
	std::vector<std::string> gamemap = data->getGameMap();
	std::map<char, std::pair<int, int>> posmap = tmap->getTilemap();

	for (int y = 0; y < data->getMapSize().second; ++y) {
		for (int x = 0; x < data->getMapSize().first; ++x) {
			if (posmap.find(gamemap[y][x]) == posmap.end())
				continue;
			zone = new SDL_Rect{xx + x * tmap->getScale(), y * tmap->getScale(), tmap->getScale(), tmap->getScale()};
			clip = new SDL_Rect{posmap[gamemap[y][x]].first + 1, posmap[gamemap[y][x]].second + 1, tmap->getScale() - 1, tmap->getScale() - 1};
			if (SDL_RenderCopyEx(render, boxes["map"], clip, zone, 0.0, NULL, SDL_FLIP_NONE))
				throw Handler("SDL2 lib", "map rendering exception");
		}
	}
}

void SdlDisplayModule::renderInfos(int mwidth, int mscale)
{
	int w, h;
	SDL_Rect box;
	int xlft = 640 / 2 + mwidth * mscale / 2;
	int xrgt = 640 / 2 - mwidth * mscale / 2;

	SDL_QueryTexture(boxes["player"], NULL, NULL, &w, &h);
	box = {xrgt - w * 3 / 4, 10, w * 3 / 4, h * 3 / 4};
	SDL_RenderCopy(render, boxes["player"], NULL, &box);

	SDL_QueryTexture(boxes["input"], NULL, NULL, &w, &h);
	box = {xrgt - w * 5 / 6, 32, w * 5 / 6, h * 5 / 6};
	SDL_RenderCopy(render, boxes["input"], NULL, &box);

	SDL_QueryTexture(boxes["gamescore"], NULL, NULL, &w, &h);
	box = {xlft, 10, w * 3 / 4, h * 3 / 4};
	SDL_RenderCopy(render, boxes["gamescore"], NULL, &box);

	SDL_QueryTexture(boxes["pscor"], NULL, NULL, &w, &h);
	box = {xlft, 32, w * 5 / 6, h * 5 / 6};
	SDL_RenderCopy(render, boxes["pscor"], NULL, &box);

	SDL_QueryTexture(boxes["controls"], NULL, NULL, &w, &h);
	box = {640 / 2 - w * 5 / 6 / 2, mwidth * mscale, w * 5 / 6, h * 5 / 6};
	SDL_RenderCopy(render, boxes["controls"], NULL, &box);

	SDL_QueryTexture(boxes["keyN"], NULL, NULL, &w, &h);
	box = {xrgt, mwidth * mscale + 30, w * 3 / 4, h * 3 / 4};
	SDL_RenderCopy(render, boxes["keyN"], NULL, &box);
	SDL_QueryTexture(boxes["keyO"], NULL, NULL, &w, &h);
	box = {xlft - w * 3 / 4, mwidth * mscale + 30, w * 3 / 4, h * 3 / 4};
	SDL_RenderCopy(render, boxes["keyO"], NULL, &box);
	SDL_QueryTexture(boxes["keyM"], NULL, NULL, &w, &h);
	box = {xrgt, mwidth * mscale + 60, w * 3 / 4, h * 3 / 4};
	SDL_RenderCopy(render, boxes["keyM"], NULL, &box);
	SDL_QueryTexture(boxes["keyX"], NULL, NULL, &w, &h);
	box = {xlft - w * 3 / 4, mwidth * mscale + 60, w * 3 / 4, h * 3 / 4};
	SDL_RenderCopy(render, boxes["keyX"], NULL, &box);
}

void SdlDisplayModule::updateDisplay(IGameModule *currentGame)
{
	ITilemap *tmap = currentGame->getTilemap();
	static std::string tilep = tmap->getTilemapPath().c_str();
	static int prevscor = -1;
	int w, h;

	if (prevscor != currentGame->getScore()) {
		prevscor = currentGame->getScore();
		SDL_DestroyTexture(boxes["pscor"]);
		genSprite("pscor", SDL_FONT, std::to_string(currentGame->getScore()).c_str());
	}
	if (SDL_QueryTexture(boxes["map"], NULL, NULL, &w, &h) || tilep != tmap->getTilemapPath().c_str()) {
		SDL_DestroyTexture(boxes["map"]);
		genSprite("map", tmap->getTilemapPath().c_str(), NULL);
		tilep = tmap->getTilemapPath().c_str();
	}


	SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(render);
	SDL_RenderCopy(render, boxes["back"], NULL, NULL);
	printMap(currentGame, tmap);
	printObjs(currentGame, tmap);
	renderInfos(currentGame->getMapSize().first, tmap->getScale());
	SDL_RenderPresent(render);
}

void SdlDisplayModule::printText(std::string texts, long timeout)
{
	int w, h;
	SDL_Rect box;

	genSprite("msgbox", SDL_FONT, texts.c_str());//gentext

	SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(render);
	SDL_RenderCopy(render, boxes["back"], NULL, NULL);

	SDL_QueryTexture(boxes["msgbox"], NULL, NULL, &w, &h);
	box = {640 / 2 - w / 2, 480 / 2, w, h};
	SDL_RenderCopy(render, boxes["msgbox"], NULL, &box);

	SDL_RenderPresent(render);
	usleep(timeout);
}

void SdlDisplayModule::renderMenu()
{
	int w, h, x, y;
	SDL_Rect box;

	SDL_QueryTexture(boxes["title"], NULL, NULL, &w, &h);
	box = {640 / 2 - w / 2, 40, w, h};
	SDL_RenderCopy(render, boxes["title"], NULL, &box);

	SDL_QueryTexture(boxes["name"], NULL, NULL, &w, &h);
	box = {640 / 2 - w / 2, 290, w, h};
	SDL_RenderCopy(render, boxes["name"], NULL, &box);

	SDL_QueryTexture(boxes["input"], NULL, NULL, &w, &h);
	box = {640 / 2 - w / 6 * 2, 310, w / 3 * 2, h / 3 * 2};
	SDL_RenderCopy(render, boxes["input"], NULL, &box);

	SDL_QueryTexture(boxes["library"], NULL, NULL, &w, &h);
	box = {640 / 4 - w / 2, 150, w, h};
	SDL_RenderCopy(render, boxes["library"], NULL, &box);

	SDL_QueryTexture(boxes["game"], NULL, NULL, &w, &h);
	box = {640 / 4 * 3 - w / 2, 150, w, h};
	SDL_RenderCopy(render, boxes["game"], NULL, &box);

	SDL_GetMouseState(&x, &y);
	SDL_QueryTexture(boxes["play"], NULL, NULL, &w, &h);
	box = {640 / 2 - w / 2, 375, w, h};
	if (x >= 640 / 2 - w / 2 && x <= 640 / 2 + w / 2 && y >= 375 && y <= 375 + h)
		box = {640 / 2 - w / 2, 373, w, h};
	SDL_RenderCopy(render, boxes["play"], NULL, &box);

	SDL_QueryTexture(boxes["score"], NULL, NULL, &w, &h);
	box = {640 / 2 - w / 2, 430, w, h};
	if (x >= 640 / 2 - w / 2 && x <= 640 / 2 + w / 2 && y >= 430 && y <= 430 + h)
		box = {640 / 2 - w / 2, 432, w, h};
	SDL_RenderCopy(render, boxes["score"], NULL, &box);
}

int SdlDisplayModule::checkButtons(SDL_Event *ev)
{
	SDL_Rect box;
	int x, y, w, h;

	SDL_GetMouseState(&x, &y);
	for (int i = 0; i < 5; ++i) {
		if (boxes.find(std::to_string(i)) != boxes.end()) {
		SDL_QueryTexture(boxes[std::to_string(i)], NULL, NULL, &w, &h);
		if (x < 640 / 4 - w / 3 || x > 640 / 4 - w / 3 + w / 3 * 2 ||
		y < 175 + (i * 20) || y > 175 + (i * 20) + h / 3 * 2 || (!x && !y))
			box = {640 / 4 - w / 3, 175 + (i * 20), w / 3 * 2, h / 3 * 2};
		else {
			box = {640 / 4 - w / 3 - 1, 175 + (i * 20) - 1, w / 3 * 2, h / 3 * 2};
			if (ev && ev->type == SDL_MOUSEBUTTONUP)
				this->_coreProgram->setGraphicLib(this->_graphicLibName.at(i));
			SDL_RenderCopy(render, boxes[std::to_string(i)], NULL, &box);
		}
		if (!ev)
			SDL_RenderCopy(render, boxes[std::to_string(i)], NULL, &box);
		}
		if (boxes.find(std::to_string(i + 100)) != boxes.end()) {
		SDL_QueryTexture(boxes[std::to_string(i + 100)], NULL, NULL, &w, &h);
		if (x < 640 / 4 * 3 - w / 3 || x > 640 / 4 * 3 + w / 3 ||
		y < 175 + (i * 20) || y > 175 + (i * 20) + h / 3 * 2 || (!x && !y))
			box = {640 / 4 * 3 - w / 3, 175 + (i * 20), w / 3 * 2, h / 3 * 2};
		else {
			box = {640 / 4 * 3 - w / 3 - 1, 175 + (i * 20) - 1, w / 3 * 2, h / 3 * 2};
			if (ev && ev->type == SDL_MOUSEBUTTONUP) {
				if (this->gameId != -1 && this->gameId != i) {
					std::string str = this->_gameLibName.at(this->gameId);
					genSprite(std::to_string(this->gameId + 100), SDL_FONT, str.c_str());
				}
				this->gameId = i;
				std::string tmp = "* " + this->_gameLibName.at(i);
				this->_coreProgram->setGameLib(this->_gameLibName.at(i));
				genSprite(std::to_string(i + 100), SDL_FONT, tmp.c_str());
			}
			SDL_RenderCopy(render, boxes[std::to_string(i + 100)], NULL, &box);
		}
		if (!ev)
			SDL_RenderCopy(render, boxes[std::to_string(i + 100)], NULL, &box);
		}
	}
	SDL_QueryTexture(boxes["play"], NULL, NULL, &w, &h);
	if (ev && ev->type == SDL_MOUSEBUTTONUP && x >= 640 / 2 - w / 2 && x <= 640 / 2 + w / 2 && y >= 375 && y <= 375 + h) {
		if (_userName.size() < 3 || _userName == "" || _userName.find_first_not_of(' ') == std::string::npos) {
			_userName += "x";
			return (0);
		}
		if (this->gameId < 0)
			this->_coreProgram->setGameLib(this->_gameLibName.at(++this->gameId));
		SDL_StopTextInput();
		return (1);
	}
	SDL_QueryTexture(boxes["score"], NULL, NULL, &w, &h);
	if (ev && ev->type == SDL_MOUSEBUTTONUP && x >= 640 / 2 - w / 2 && x <= 640 / 2 + w / 2 && y >= 430 && y <= 430 + h) {
		if (_userName.size() < 3 || _userName == "" || _userName.find_first_not_of(' ') == std::string::npos) {
			_userName += "x";
			return (0);
		}
		if (this->gameId < 0)
			this->_coreProgram->setGameLib(this->_gameLibName.at(++this->gameId));
		this->_coreProgram->pushScores();

		genSprite(std::to_string(4242), SDL_FONT, this->_gameLibName.at(gameId).c_str());
		for (size_t u = 0; u < this->_scores.size() && u < 10; ++u)
			genSprite(std::to_string((u + 1) * -1), SDL_FONT, this->_scores.at(u).c_str());
		menuMode = 1;
	}
	return (0);
}

void SdlDisplayModule::showScore()
{
	SDL_Event ev;
	SDL_Rect box;
	int x, y, w, h;

	SDL_QueryTexture(boxes["4242"], NULL, NULL, &w, &h);
	box = {640 / 2 - w * 5 / 4 / 2, 65, w * 5 / 4, h * 5 / 4};
	SDL_RenderCopy(render, boxes["4242"], NULL, &box);

	for (size_t u = 0; u < this->_scores.size() && u < 10; ++u) {
		SDL_QueryTexture(boxes[std::to_string((u + 1) * -1)], NULL, NULL, &w, &h);
		box = {640 / 2 - w * 4 / 5 / 2, 150 + (int)u * 25, w * 4 / 5, h * 4 / 5};
		SDL_RenderCopy(render, boxes[std::to_string((u + 1) * -1)], NULL, &box);
	}
	SDL_GetMouseState(&x, &y);
	SDL_QueryTexture(boxes["scorex2"], NULL, NULL, &w, &h);
	box = {640 / 2 - w / 2, 30, w, h};
	if (x >= 640 / 2 - w / 2 && x <= 640 / 2 + w / 2 && y >= 30 && y <= 30 + h)
		box = {640 / 2 - w / 2, 28, w, h};
	SDL_RenderCopy(render, boxes["scorex2"], NULL, &box);
	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT)
			exit(0);
		if (ev.type == SDL_MOUSEBUTTONUP && x >= 640 / 2 - w / 2 && x <= 640 / 2 + w / 2 && y >= 28 && y <= 28 + h) {
			menuMode = 0;
		}
	}
	SDL_RenderPresent(render);
}

int SdlDisplayModule::displayMenu()
{
	//printf("MENU\n");
	SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(render);
	SDL_Event ev;
	std::string buf = "";
	std::string cmp = _userName;

	if (!SDL_IsTextInputActive())
		SDL_StartTextInput();
	SDL_RenderCopy(render, boxes["back"], NULL, NULL);
	if (menuMode == 1) {
		this->showScore();
		return (0);
	}
	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT) {
			this->destroy();
			exit(0);
		}
		if (checkButtons(&ev))
			return (1);
		if (ev.type == SDL_KEYDOWN) {
			if (ev.key.keysym.sym == SDLK_BACKSPACE && _userName.length() > 0)
			_userName.pop_back();
			else
			buf = (SDL_GetKeyName(ev.key.keysym.sym));
		}
		else if (ev.type == SDL_TEXTINPUT && _userName.size() < 16)
		_userName += ev.text.text;
	}
	checkButtons(NULL);
	renderMenu();
	_userName = (_userName == "") ? " " : _userName;
	if (cmp != _userName)
	genSprite("input", SDL_FONT, _userName.c_str());
	if (buf != "") {
		std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
		//this->keyAction(const_cast<char*>(buf.data()));
	}
	SDL_RenderPresent(render);
	return (0);
}

void SdlDisplayModule::initMenu()
{
	std::size_t pos;
	std::string imgs[11] = {
		P_SDLBACK,
		P_SDLGAME,
		P_SDLLIBR,
		P_SDLNAME,
		P_SDLPLAY,
		P_SDLSCOR,
		P_SDLSCOX,
		P_SDLTITL,
		P_SDLCTRL,
		P_SDLGSCR,
		P_SDLPLYR
	};

	this->_coreProgram->pushGraphicName();
	for(std::size_t j = 0; j < this->_graphicLibName.size() ; ++j)
		genSprite(std::to_string(j), SDL_FONT, this->_graphicLibName.at(j).c_str());
	this->_coreProgram->pushGameName();
	for(std::size_t j = 0; j < this->_gameLibName.size() ; ++j)
	genSprite(std::to_string(j + 100), SDL_FONT, this->_gameLibName.at(j).c_str());
	for (int i = 0; i < 11; ++i) {
		pos = imgs[i].find(".png");
		genSprite(imgs[i].substr(10, pos - 10), imgs[i].c_str(), NULL);
	}
	genSprite("input", SDL_FONT, _userName.c_str());
	genSprite("keyN", SDL_FONT, CTRL_N);
	genSprite("keyO", SDL_FONT, CTRL_O);
	genSprite("keyM", SDL_FONT, CTRL_M);
	genSprite("keyX", SDL_FONT, CTRL_X);
	if (this->_gameLibName.size() == 0) {
		this->destroy();
		throw Handler("SDL2lib", "no games to play");
	}
	this->gameId = -1;
}

std::string SdlDisplayModule::getKey()
{
	SDL_Event ev;
	std::string buf;

	if (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT)
			exit(0);
		if (ev.type == SDL_KEYDOWN) {
			buf = (SDL_GetKeyName(ev.key.keysym.sym));
		}
	}
	std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
	//	std::cout << buf << "\n";
	this->keyAction(buf);
	return (buf);
}

const std::string &SdlDisplayModule::getName() const
{
	return (_name);
}

void SdlDisplayModule::keyAction(std::string key)
{
	if (key == EXIT_KEY) {
		this->destroy();
		exit(0);
	}
	if (key == NEXT_LIB_KEY) {
		this->_coreProgram->nextGraphicLib();
	}
	if (key == NEXT_GAME_KEY) {
		this->_coreProgram->nextGameLib();
	}
	if (key == PREV_LIB_KEY) {
		this->_coreProgram->prevGraphicLib();
	}
	if (key == PREV_GAME_KEY) {
		this->_coreProgram->prevGameLib();
	}
}

void SdlDisplayModule::setHandler(void *handler)
{
	this->_handler = handler;
}

const std::string &SdlDisplayModule::getUserName() const
{
	return (this->_userName);
}

void SdlDisplayModule::setUserName(std::string userName)
{
	this->_userName = userName;
}

void *SdlDisplayModule::getHandler() const
{
	return (this->_handler);
}
