//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// NcurseDisplayModule.cpp
//
#include "Error.hpp"
#include "DefaultKeys.hpp"
#include <algorithm>
#include <unistd.h>
#include <string.h>
#include <menu.h>
#include "IGameModule.hpp"
#include "NcurseDisplayModule.hpp"
#include <term.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <termios.h>
#include <curses.h>
#include <ncurses.h>
#include <iostream>
#include <cmath>

NcurseDisplayModule *refForSignal;

extern "C" {
	void __attribute__((constructor)) calledFirst();
	void __attribute__((destructor)) calledLast();
	static NcurseDisplayModule *myLib;

	void	printResize(void)
	{
		if (LINES < 30 || COLS < 60)
		{
			while (LINES < 30 || COLS < 60) {
				clear();
				move((LINES / 2), (COLS / 2) - (28 / 2));
				printw("Enlarge the terminal to play");
				refresh();
				move(0, 0);
				getch();
			}
			clear();
		}
	}

	void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
	{
		int length, x, y;
		float temp;

		if(win == NULL)
		win = stdscr;
		getyx(win, y, x);
		if(startx != 0)
		x = startx;
		if(starty != 0)
		y = starty;
		if(width == 0)
		width = 80;

		length = strlen(string);
		temp = (width - length)/ 2;
		x = startx + (int)temp;
		wattron(win, color);
		mvwprintw(win, y, x, "%s", string);
		wattroff(win, color);
		refresh();
	}

	void    init_curses()
	{
		initscr();
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_GREEN, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		init_pair(5, COLOR_BLUE, COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_CYAN, COLOR_BLACK);
		init_pair(8, COLOR_BLACK, COLOR_BLACK);
		curs_set(0);
		noecho();
	}

	void NcurseSigHandler(int signo)
	{
		if (signo == SIGINT) {
			refForSignal->destroy();
			exit(0);
		}
	}

	void keyPush(std::string key)
	{
		char *smkx = tigetstr(key.c_str());

		write(1, smkx, strlen(smkx));
	}

	std::string getTextInput()
	{
		char buffer[255];
		int i = 0;

		i = read(0, buffer, 254);
		buffer[i] = 0;
		return (std::string(buffer));
	}

	void calledFirst()
	{
		myLib = new NcurseDisplayModule;
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

NcurseDisplayModule::NcurseDisplayModule() : _name("NcurseLib"), _userName("Bobby")
{
	ioctl(0, TCGETS, &this->oldTerm);
	setupterm(NULL, fileno(stdout), NULL);
	this->oldHandler = signal(SIGINT, NcurseSigHandler);
	signal(SIGINT, this->oldHandler);
	refForSignal = this;
	initKeyDictionary();
	initColorMap();
}

void NcurseDisplayModule::init(ICoreProgram *coreProgram)
{
	this->_coreProgram = coreProgram;
	signal(SIGINT, NcurseSigHandler);
	setRead(0);
	init_curses();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	keyPush("smkx");
	this->myLibMenuInit();
	this->myGameMenuInit();
	myMenuWin = newwin(10, 40, 4, 4);
	set_menu_win(myLibMenu, myMenuWin);
	set_menu_sub(myLibMenu, derwin(myMenuWin, 6, 38, 3, 1));
	this->currentMenu = myLibMenu;
}

void NcurseDisplayModule::initKeyDictionary()
{
	_keyDictionary[KEY_LEFT] = LEFT_KEY;
	_keyDictionary[KEY_RIGHT] = RIGHT_KEY;
	_keyDictionary[KEY_UP] = UP_KEY;
	_keyDictionary[KEY_DOWN] = DOWN_KEY;
	_keyDictionary[' '] = SPACE_KEY;
}

void NcurseDisplayModule::initColorMap()
{
	_colorMap['a'] = A_REVERSE | COLOR_PAIR(3);
	_colorMap['A'] = A_REVERSE | COLOR_PAIR(3);
	_colorMap['b'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['_'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['|'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['d'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['q'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['p'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['T'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['t'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['u'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['U'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['-'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['='] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['K'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['k'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['L'] = A_REVERSE | COLOR_PAIR(1);
	_colorMap['C'] = A_REVERSE | COLOR_PAIR(4);
	_colorMap['c'] = A_REVERSE | COLOR_PAIR(4);
	_colorMap['v'] = A_REVERSE | COLOR_PAIR(4);
	_colorMap['V'] = A_REVERSE | COLOR_PAIR(4);
	_colorMap[' '] = A_REVERSE | COLOR_PAIR(8);
	_colorMap['*'] = A_REVERSE | COLOR_PAIR(2);
	_colorMap['f'] = A_REVERSE | COLOR_PAIR(2);
	_colorMap['F'] = A_REVERSE | COLOR_PAIR(2);
	_colorMap['g'] = A_REVERSE | COLOR_PAIR(2);
	_colorMap['G'] = A_REVERSE | COLOR_PAIR(2);
	_colorMap['i'] = A_REVERSE | COLOR_PAIR(3);
	_colorMap['I'] = A_REVERSE | COLOR_PAIR(3);
	_colorMap['y'] = A_REVERSE | COLOR_PAIR(3);
	_colorMap['Y'] = A_REVERSE | COLOR_PAIR(3);
	_colorMap['e'] = A_REVERSE | COLOR_PAIR(4);
	_colorMap['E'] = A_REVERSE | COLOR_PAIR(4);
	_colorMap['j'] = A_REVERSE | COLOR_PAIR(4);
	_colorMap['J'] = A_REVERSE | COLOR_PAIR(4);
	_colorMap['1'] = A_REVERSE | COLOR_PAIR(6);
	_colorMap['2'] = A_REVERSE | COLOR_PAIR(6);
	_colorMap['3'] = A_REVERSE | COLOR_PAIR(6);
	_colorMap['4'] = A_REVERSE | COLOR_PAIR(6);
	_colorMap['5'] = A_REVERSE | COLOR_PAIR(5);
	_colorMap['6'] = A_REVERSE | COLOR_PAIR(5);
	_colorMap['7'] = A_REVERSE | COLOR_PAIR(5);
	_colorMap['8'] = A_REVERSE | COLOR_PAIR(5);
}

void NcurseDisplayModule::myGameMenuInit()
{
	ITEM **myGameItems;
	unsigned int i;

	this->_coreProgram->pushGameName();
	if (this->_gameLibName.size() == 0) {
		this->destroy();
		throw Handler("NcurseDisplayModule", "no games to play");
	}
	myGameItems = new ITEM*[this->_gameLibName.size() + 1];
	for(i = 0; i < this->_gameLibName.size() ; ++i) {
		myGameItems[i] = new_item(strdup(this->_gameLibName.at(i).c_str()), NULL);
	}
	myGameItems[i] = new_item(NULL, NULL);
	myGameMenu = new_menu((ITEM **)myGameItems);
	set_menu_format(myGameMenu, 5, 1);
	set_menu_mark(myGameMenu, " * ");
	set_menu_opts(myGameMenu, O_ONEVALUE);
}

void NcurseDisplayModule::myScoreMenuInit()
{
	ITEM **myScoreItems;
	unsigned int i;

	this->_coreProgram->pushScores();
	myScoreItems = new ITEM*[this->_scores.size() + 1];
	for(i = 0; i < this->_scores.size() ; ++i) {
		myScoreItems[i] = new_item(strdup(this->_scores.at(i).c_str()), NULL);
	}
	myScoreItems[i] = new_item(NULL, NULL);
	myScoreMenu = new_menu((ITEM **)myScoreItems);
	set_menu_format(myScoreMenu, 5, 1);
	set_menu_opts(myScoreMenu, O_ONEVALUE);
}

void NcurseDisplayModule::myLibMenuInit()
{
	ITEM **myLibItems;
	unsigned int i;

	this->_coreProgram->pushGraphicName();
	myLibItems = new ITEM*[this->_graphicLibName.size() + 1];
	for(i = 0; i < this->_graphicLibName.size() ; ++i) {
		myLibItems[i] = new_item(strdup(this->_graphicLibName.at(i).c_str()), NULL);
	}
	myLibItems[i] = new_item(NULL, NULL);
	myLibMenu = new_menu((ITEM **)myLibItems);
	set_menu_format(myLibMenu, 5, 1);
	set_menu_mark(myLibMenu, " * ");
	set_menu_opts(myLibMenu, O_ONEVALUE);
}

void NcurseDisplayModule::destroy()
{
	clear();
	delwin(myMenuWin);
	endwin();
	signal(SIGINT, this->oldHandler);
	setRead(1);
	keyPush("rmkx");
}

void NcurseDisplayModule::setGraphicLibName(std::vector<std::string> graphicLibName)
{
	this->_graphicLibName = graphicLibName;
}

void NcurseDisplayModule::setGameLibName(std::vector<std::string> gameLibName)
{
	this->_gameLibName = gameLibName;
}

void NcurseDisplayModule::setScore(std::vector<std::string> scores)
{
	this->_scores = scores;
}

void NcurseDisplayModule::setHandler(void *handler)
{
	this->_handler = handler;
}

void printRules(IGameModule *currentGame, std::vector<std::string> gameMap)
{
	unsigned int i = 0;
	unsigned int j = 0;
	std::vector<std::string> _rules = {"RULES", "",
						NEXT_LIB_HINT, PREV_LIB_HINT,
						NEXT_GAME_HINT, PREV_GAME_HINT,
						RESTART_GAME_HINT, EXIT_HINT,
						MENU_HINT, "", "", "Current Game :",
						currentGame->getName(), "", "",
						"Score :", std::to_string(currentGame->getScore())};
	while (i < _rules.size()) {
		j = 0;
		move((LINES / 2) - (gameMap.size() / 2) + i, gameMap[0].size() * 4);
		while (j < _rules[i].size()) {
			addch(_rules[i][j]);
			j++;
		}
		i++;
	}
}

void NcurseDisplayModule::printGameMap(std::vector<std::string> gameMap, std::vector<objPos_t> objPos)
{
	unsigned int i = 0;
	unsigned int j = 0;

	while (i < objPos.size()) {
		gameMap[round(objPos[i].y)][round(objPos[i].x)] = objPos[i].value;
		i++;
	}
	i = 0;
	while (i < gameMap.size()) {
		j = 0;
		move((LINES / 2) - (gameMap.size() / 2) + i,  (COLS - (gameMap[i].size())) / 2 - gameMap[i].size());
		while (j < gameMap[i].size()) {
			addch(gameMap[i][j] | _colorMap[gameMap[i][j]]);
			addch(gameMap[i][j] | _colorMap[gameMap[i][j]]);
			j++;
		}
		i++;
	}
}

void NcurseDisplayModule::updateDisplay(IGameModule *currentGame)
{
	std::vector<std::string> gameMap = currentGame->getGameMap();
	std::vector<objPos_t> objPos = currentGame->getObjPos();

	printResize();
	clear();
	printGameMap(gameMap, objPos);
	printRules(currentGame, gameMap);
	refresh();
	move(0, 0);
}

void NcurseDisplayModule::printText(std::string text, long timeout)
{
	printResize();
	clear();
	move((LINES / 2), (COLS / 2) - (text.size() / 2));
	printw("%s", text.c_str());
	refresh();
	usleep(timeout);
	move(0, 0);
}

const std::string &NcurseDisplayModule::getUserName() const
{
	return (this->_userName);
}

void NcurseDisplayModule::setUserName(std::string userName)
{
	userName.erase(std::remove(userName.begin(), userName.end(), '\n'), userName.end());
	this->_userName = userName;
}

void NcurseDisplayModule::getUserInput()
{
	std::string c;

	unpost_menu(this->currentMenu);
	wclear(myMenuWin);
	box(myMenuWin, 0, 0);
	print_in_middle(myMenuWin, 1, 0, 40, const_cast<char *>("Enter your name"), COLOR_PAIR(1));
	mvwaddch(myMenuWin, 2, 0, ACS_LTEE);
	mvwhline(myMenuWin, 2, 1, ACS_HLINE, 38);
	mvwaddch(myMenuWin, 2, 39, ACS_RTEE);
	move(LINES - 2, 0);
	clrtoeol();
	mvprintw(LINES - 2, 0, "Press <enter> to launch the game");
	move(10, 20);
	wrefresh(myMenuWin);
	refresh();
	curs_set(1);
	echo();
	setRead(1);
	c = getTextInput();
	setRead(0);
	curs_set(0);
	noecho();
	this->setUserName(c);
}

void NcurseDisplayModule::switchMenu(MENU *newMenu, std::string menuText, std::string menuTip)
{
	unpost_menu(this->currentMenu);
	wclear(myMenuWin);
	set_menu_win(newMenu, myMenuWin);
	set_menu_sub(newMenu, derwin(myMenuWin, 6, 38, 3, 1));
	this->currentMenu = newMenu;
	this->myMenuText = menuText;
	this->myMenuTip = menuTip;
}

int NcurseDisplayModule::menuValidation()
{
	if (this->currentMenu == this->myLibMenu) {
		if (std::string(item_name(current_item(this->currentMenu))) != this->getName()) {
			menuRun = 0;
			this->_coreProgram->setGraphicLib(item_name(current_item(this->currentMenu)));
		}
		switchMenu(this->myGameMenu, "Select gaming library", "Press <space> to select a game library");
	}
	else if (this->currentMenu == this->myGameMenu) {
		this->_coreProgram->setGameLib(item_name(current_item(this->currentMenu)));
		this->myScoreMenuInit();
		switchMenu(this->myScoreMenu, "Scoreboard", "Press <space> to skip");
	}
	else if (this->currentMenu == this->myScoreMenu) {
		this->getUserInput();
		switchMenu(this->myLibMenu, "Select graphical library", "Press <space> to select a graphic library");
		clear();
		refresh();
		menuRun = 0;
		return (1);
	}
	return (0);
}

void NcurseDisplayModule::printMenu()
{
	printResize();
	box(myMenuWin, 0, 0);
	print_in_middle(myMenuWin, 1, 0, 40, const_cast<char *>(myMenuText.c_str()), COLOR_PAIR(1));
	mvwaddch(myMenuWin, 2, 0, ACS_LTEE);
	mvwhline(myMenuWin, 2, 1, ACS_HLINE, 38);
	mvwaddch(myMenuWin, 2, 39, ACS_RTEE);
	move(LINES - 2, 0);
	clrtoeol();
	mvprintw(LINES - 2, 0, const_cast<char *>(myMenuTip.c_str()));
	refresh();
	post_menu(this->currentMenu);
	wrefresh(myMenuWin);
}

int NcurseDisplayModule::displayMenu()
{
	std::string c;

	menuRun = 1;
	switchMenu(this->myLibMenu, "Select graphical library", "Press <space> to select a graphic library");
	clear();
	while (menuRun) {
		printMenu();
		c = translateKey(getch());
		if (c == DOWN_KEY)
			menu_driver(this->currentMenu, REQ_DOWN_ITEM);
		if (c == UP_KEY)
			menu_driver(this->currentMenu, REQ_UP_ITEM);
		if (c == SPACE_KEY)
		{
			if (menuValidation())
				return (1);
		}
		if (!menuRun)
			break;
	}
	return (0);
}

std::string NcurseDisplayModule::getKey()
{
	std::string buffer = translateKey(getch());

	this->keyAction(buffer);
	return (buffer);
}

const std::string &NcurseDisplayModule::getName() const
{
	return (_name);
}

void NcurseDisplayModule::keyAction(std::string key)
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
		clear();
		refresh();
	}
	if (key == PREV_LIB_KEY) {
		this->_coreProgram->prevGraphicLib();
	}
	if (key == PREV_GAME_KEY) {
		this->_coreProgram->prevGameLib();
		clear();
		refresh();
	}
}

std::string NcurseDisplayModule::translateKey(int key)
{
	if (this->_keyDictionary[key] == "") {
		this->_keyDictionary[key].push_back(key);
		std::transform(this->_keyDictionary[key].begin(),
		this->_keyDictionary[key].end(),
		this->_keyDictionary[key].begin(),
		::tolower);
	}
	return (std::string(this->_keyDictionary[key]));
}

int	NcurseDisplayModule::setRead(int state)
{
	struct termios	newRead;

	if (state == 0)
	{
		if (ioctl(0, TCGETS, &newRead) == -1)
			throw Handler("NcurseDisplayModule::setRead", "ioctl get failed");
		newRead.c_lflag &= ~ECHO;
		newRead.c_lflag &= ~ICANON;
		newRead.c_cc[VMIN] = 0;
		newRead.c_cc[VTIME] = 1;
		if (ioctl(0, TCSETS, &newRead) == -1)
			throw Handler("NcurseDisplayModule::setRead", "ioctl set failed");
	}
	else
		if (ioctl(0, TCSETS, &oldTerm) == -1)
			throw Handler("NcurseDisplayModule::setRead", "ioctl reset failed");
	return (0);
}

void *NcurseDisplayModule::getHandler() const
{
	return (this->_handler);
}
