//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// SdlDisplayModule.hpp
//

#ifndef SDLDISPLAYMODULE_HPP_
# define SDLDISPLAYMODULE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include "Error.hpp"
#include "IGameModule.hpp"
#include "IDisplayModule.hpp"

#define CTRL_N "N switch graphics"
#define CTRL_O "switch game O"
#define CTRL_M "M menu"
#define CTRL_X "quit X"

class SdlDisplayModule : public IDisplayModule {
public:
	SdlDisplayModule();
	~SdlDisplayModule() = default;
	void init(ICoreProgram *);
	void setHandler(void *);
	void updateDisplay(IGameModule *);
	void printMap(IGameModule *, ITilemap *);
	void printObjs(IGameModule *, ITilemap *);
	void destroy();
	void *getHandler() const;
	std::string getKey();
	void keyAction(std::string);
	const std::string &getName() const;
	int displayMenu();
	void renderMenu();
	void renderInfos(int, int);
	int checkButtons(SDL_Event *);
	void printText(std::string, long);
	void initMenu();
	void showScore();
	void genSprite(std::string, const char *, const char *);
	void setGraphicLibName(std::vector<std::string>);
	void setGameLibName(std::vector<std::string>);
	void setScore(std::vector<std::string>);
	const std::string &getUserName() const;
	void setUserName(std::string userName);
	SDL_Renderer *render;
	SDL_Window *win;
	std::map<std::string, SDL_Texture *> boxes;

private:
	int gameId;
	int menuMode;
	std::string _name;
	void *_handler;
	std::vector<std::string> libs;
	ICoreProgram *_coreProgram;
	std::vector<std::string> _graphicLibName;
	std::vector<std::string> _gameLibName;
	std::vector<std::string> _scores;
	std::string _userName;
};


#endif // SDLDISPLAYMODULE_HPP_
