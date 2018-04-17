//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// NcurseDisplayModule.hpp
//

#ifndef NCURSEDISPLAYMODULE_HPP_
# define NCURSEDISPLAYMODULE_HPP_

#include "IDisplayModule.hpp"
#include <term.h>
#include <menu.h>
#include <signal.h>
#include <map>
#include "IGameModule.hpp"

class NcurseDisplayModule : public IDisplayModule {
public:
	NcurseDisplayModule();
	~NcurseDisplayModule() = default;
	void init(ICoreProgram *);
	void setHandler(void *);
	void *getHandler() const;
	void updateDisplay(IGameModule *);
	void destroy();
	std::string getKey();
	void keyAction(std::string);
	const std::string &getName() const;
	int displayMenu();
	void run();
	void printText(std::string, long);
	int setRead(int);
	void switchMenu(MENU *, std::string, std::string);
	void myLibMenuInit();
	void setGraphicLibName(std::vector<std::string>);
	void setGameLibName(std::vector<std::string>);
	void setScore(std::vector<std::string>);
	void myGameMenuInit();
	void myScoreMenuInit();
	const std::string &getUserName() const;
	void setUserName(std::string userName);
	void getUserInput();
	int menuValidation();
	std::string translateKey(int key);
	void initKeyDictionary();
	void initColorMap();
	void printGameMap(std::vector<std::string> gameMap, std::vector<objPos_t> objPos);
	void printMenu();
private:
	std::string _name;
	std::map<int, std::string> _keyDictionary;
	void *_handler;
	ICoreProgram *_coreProgram;
	MENU *myLibMenu;
	MENU *myGameMenu;
	MENU *myScoreMenu;
	MENU *currentMenu;
	std::string myMenuText;
	std::string myMenuTip;
	WINDOW *myMenuWin;
	std::string _userName;
	std::vector<std::string> _graphicLibName;
	std::vector<std::string> _gameLibName;
	std::vector<std::string> _scores;
	int menuRun;
	struct termios oldTerm;
	sighandler_t oldHandler;
	std::map<char, int> _colorMap;
};

#endif // NCURSEDISPLAYMODULE_HPP_
