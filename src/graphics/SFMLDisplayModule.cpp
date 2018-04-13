//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// SFMLDisplayModule.cpp
//

#include "Paths.hpp"
#include "ITilemap.hpp"
#include "Error.hpp"
#include "DefaultKeys.hpp"
#include "SFMLDisplayModule.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

extern "C" {
	void __attribute__((constructor)) calledFirst();
	void __attribute__((destructor)) calledLast();
	static SFMLDisplayModule *myLib;

	void calledFirst()
	{
		myLib = new SFMLDisplayModule;
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

std::string SFMLDisplayModule::detectKey()
{
	#define DETECT_KEY(identifier) if (sf::Keyboard::isKeyPressed(sf::Keyboard::identifier)) return std::string(#identifier)
	sf::Event event;
	while (_myWindow->pollEvent(event));

	DETECT_KEY(Unknown);
	DETECT_KEY(A);
	DETECT_KEY(B);
	DETECT_KEY(C);
	DETECT_KEY(D);
	DETECT_KEY(E);
	DETECT_KEY(F);
	DETECT_KEY(G);
	DETECT_KEY(H);
	DETECT_KEY(I);
	DETECT_KEY(J);
	DETECT_KEY(K);
	DETECT_KEY(L);
	DETECT_KEY(M);
	DETECT_KEY(N);
	DETECT_KEY(O);
	DETECT_KEY(P);
	DETECT_KEY(Q);
	DETECT_KEY(R);
	DETECT_KEY(S);
	DETECT_KEY(T);
	DETECT_KEY(U);
	DETECT_KEY(V);
	DETECT_KEY(W);
	DETECT_KEY(X);
	DETECT_KEY(Y);
	DETECT_KEY(Z);
	DETECT_KEY(Num0);
	DETECT_KEY(Num1);
	DETECT_KEY(Num2);
	DETECT_KEY(Num3);
	DETECT_KEY(Num4);
	DETECT_KEY(Num5);
	DETECT_KEY(Num6);
	DETECT_KEY(Num7);
	DETECT_KEY(Num8);
	DETECT_KEY(Num9);
	DETECT_KEY(Escape);
	DETECT_KEY(LControl);
	DETECT_KEY(LAlt);
	DETECT_KEY(LSystem);
	DETECT_KEY(RControl);
	DETECT_KEY(RShift);
	DETECT_KEY(RAlt);
	DETECT_KEY(RSystem);
	DETECT_KEY(Menu);
	DETECT_KEY(LBracket);
	DETECT_KEY(RBracket);
	DETECT_KEY(SemiColon);
	DETECT_KEY(Comma);
	DETECT_KEY(Period);
	DETECT_KEY(Quote);
	DETECT_KEY(Slash);
	DETECT_KEY(BackSlash);
	DETECT_KEY(Tilde);
	DETECT_KEY(Equal);
	DETECT_KEY(Dash);
	DETECT_KEY(Space);
	DETECT_KEY(Return);
	DETECT_KEY(BackSpace);
	DETECT_KEY(Tab);
	DETECT_KEY(PageUp);
	DETECT_KEY(PageDown);
	DETECT_KEY(End);
	DETECT_KEY(Home);
	DETECT_KEY(Insert);
	DETECT_KEY(Delete);
	DETECT_KEY(Add);
	DETECT_KEY(Subtract);
	DETECT_KEY(Multiply);
	DETECT_KEY(Divide);
	DETECT_KEY(Left);
	DETECT_KEY(Right);
	DETECT_KEY(Up);
	DETECT_KEY(Down);
	DETECT_KEY(Numpad0);
	DETECT_KEY(Numpad1);
	DETECT_KEY(Numpad2);
	DETECT_KEY(Numpad3);
	DETECT_KEY(Numpad4);
	DETECT_KEY(Numpad5);
	DETECT_KEY(Numpad6);
	DETECT_KEY(Numpad7);
	DETECT_KEY(Numpad8);
	DETECT_KEY(Numpad9);
	DETECT_KEY(F1);
	DETECT_KEY(F2);
	DETECT_KEY(F3);
	DETECT_KEY(F4);
	DETECT_KEY(F5);
	DETECT_KEY(F6);
	DETECT_KEY(F7);
	DETECT_KEY(F8);
	DETECT_KEY(F9);
	DETECT_KEY(F10);
	DETECT_KEY(F11);
	DETECT_KEY(F12);
	DETECT_KEY(F13);
	DETECT_KEY(F14);
	DETECT_KEY(F15);
	DETECT_KEY(Pause);

	#undef DETECT_KEY
	return ("");
}

SFMLDisplayModule::SFMLDisplayModule() : _name("SFML Lib"), _userName("Michel"), _myWindow(new sf::RenderWindow), _font(new sf::Font)
{
	background = new SFMLSprite(RESOURCES_PATH + SFML_PATH + "sfml-background.png", 0, 0);
	title = new SFMLSprite(RESOURCES_PATH + SFML_PATH + "sfml-title.png", 0, 0);
	changeLib = new SFMLSprite(RESOURCES_PATH + SFML_PATH + "sfml-change-lib.png", 0, 0);
	chooseGame = new SFMLSprite(RESOURCES_PATH + SFML_PATH + "sfml-choose-a-game.png", 0, 0);
	play = new SFMLSprite(RESOURCES_PATH + SFML_PATH + "sfml-play.png", 0, 0);
	scoreboard = new SFMLSprite(RESOURCES_PATH + SFML_PATH + "sfml-scoreboard.png", 0, 0);

	title->setPosition(title->midX(640), changeLib->midY(480) - 200);
	changeLib->setPosition(changeLib->midX(640) - 150, changeLib->midY(480) - 100);
	chooseGame->setPosition(chooseGame->midX(640) + 150, chooseGame->midY(480) - 100);
	play->setPosition(play->midX(640), play->midY(480) + 150);
	scoreboard->setPosition(scoreboard->midX(640), scoreboard->midY(480) + 178);
}

SFMLDisplayModule::~SFMLDisplayModule()
{
	this->destroy();
}

void SFMLDisplayModule::init(ICoreProgram *coreProgram)
{
	this->_coreProgram = coreProgram;
	if (!_font->loadFromFile(RESOURCES_PATH + FONT_PATH + "ARCADE_R.TTF"))
	{
		throw Handler("SFML", "error while loading font");
	}
	this->_coreProgram->pushGameName();
	if (_gameLibName.empty()) {
		throw Handler("SFML", "no games to play");
	}
	this->_coreProgram->pushGraphicName();
	if (_graphicLibName.empty()) {
		throw Handler("SFML", "no graphics modules");
	}
	this->_SMFLGraphicLibName = createSFMLTextArray(_graphicLibName, 12);
	this->_SMFLGameLibName = createSFMLTextArray(_gameLibName, 12);
	_myWindow->create(sf::VideoMode(640, 480), "Arcade", sf::Style::Close);
	_myWindow->setVerticalSyncEnabled(true);
	_myWindow->setFramerateLimit(60);
	sf::Event event;
	while (_myWindow->pollEvent(event));
	enterYourName = new sf::Text;
	enterYourName->setPosition(20, 450);
	enterYourName->setFont(*_font);
	enterYourName->setCharacterSize(14);
	enterYourName->setString("Enter your name :");
	_SFMLUsername = new sf::Text;
	_SFMLUsername->setPosition(270, 450);
	_SFMLUsername->setString(this->_userName);
	_SFMLUsername->setFont(*_font);
	_SFMLUsername->setCharacterSize(14);
	initMenuAction();
}

void SFMLDisplayModule::setHandler(void *handler)
{
	this->_handler = handler;
}

void SFMLDisplayModule::initMenuAction()
{
	_menuAction[NEXT_LIB_HINT] = NEXT_LIB_KEY;
	_menuAction[PREV_LIB_HINT] = PREV_LIB_KEY;
	_menuAction[NEXT_GAME_HINT] = NEXT_GAME_KEY;
	_menuAction[PREV_GAME_HINT] = PREV_GAME_KEY;
	_menuAction[RESTART_GAME_HINT] = RESTART_GAME_KEY;
	_menuAction[EXIT_HINT] = EXIT_KEY;
	_menuAction[MENU_HINT] = MENU_KEY;
}

std::string SFMLDisplayModule::getMenuAction(std::string str)
{
	return (this->_menuAction[str]);
}

void SFMLDisplayModule::updateDisplay(IGameModule *currentGame)
{
	SFMLTileMap map;
	ITilemap *tileMap = currentGame->getTilemap();

	map.setGameMap(currentGame->getGameMap());
	map.setPosition(_myWindow->getSize().x / 2 - (currentGame->getMapSize().second * tileMap->getScale()) / 2, 0);
	if (!map.load(tileMap->getTilemapPath(), sf::Vector2u(tileMap->getScale(), tileMap->getScale()), currentGame))
		return;
	map.updateObj(currentGame->getObjPos(), currentGame->getTilemap()->getTilemap(), sf::Vector2u(tileMap->getScale(), tileMap->getScale()), currentGame->getMapSize().first);
	_myWindow->clear(sf::Color::Black);
	_myWindow->draw(map);
	_rules = createSFMLTextArray({NEXT_LIB_HINT, PREV_LIB_HINT, NEXT_GAME_HINT, PREV_GAME_HINT, RESTART_GAME_HINT, EXIT_HINT, MENU_HINT}, 11);
	std::vector<sf::Text *> gameName = createSFMLTextArray({"Current Game :", currentGame->getName()}, 11);
	std::vector<sf::Text *> score = createSFMLTextArray({"Score : " + std::to_string(currentGame->getScore())}, 14);
	printSFMLTextArray(_rules, 5, 5);
	printSFMLTextArray(gameName, 510, 5, 0);
	printSFMLTextArray(score, 260, 400, 0);
	_myWindow->display();
}

void SFMLDisplayModule::destroy()
{
	_myWindow->close();
}

std::string SFMLDisplayModule::getKey()
{
	sf::Event event;
	sf::Text *selection;

	while (_myWindow->pollEvent(event));
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			selection = clickOnText(_rules);
			if (selection)
			{
				std::string selectedOption = selection->getString();
				this->keyAction(getMenuAction(selectedOption));
				return (getMenuAction(selectedOption));
			}
		}
	}
	std::string buf = detectKey();
	std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
	this->keyAction(buf);
	return (buf);
}

void SFMLDisplayModule::keyAction(std::string key)
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

const std::string &SFMLDisplayModule::getName() const
{
	return (this->_name);
}

const std::string &SFMLDisplayModule::getUserName() const
{
	return (this->_userName);
}

std::vector<sf::Text *> SFMLDisplayModule::createSFMLTextArray(std::vector<std::string> text, int size)
{
	std::unique_ptr<std::vector<sf::Text *>> myArray(new std::vector<sf::Text *>);
	unsigned int i = 0;

	while (i < text.size()) {
		sf::Text *myText = new sf::Text;
		myText->setFont(*this->_font);
		myText->setCharacterSize(size);
		myText->setString(text[i]);
		myArray->push_back(myText);
		i++;
	}
	return (*myArray);
}

void mouseHover(sf::Text *myArray, sf::Vector2i position)
{
	if (myArray->getGlobalBounds().contains(position.x, position.y)) {
		myArray->setFillColor(sf::Color::Cyan);
		myArray->move(-2, -2);
	}
}

void SFMLDisplayModule::printSFMLTextArray(std::vector<sf::Text *> myArray, double x, double y, bool activeMouseOver)
{
	unsigned int i = 0;
	sf::Vector2i position = sf::Mouse::getPosition(*_myWindow);

	while (i < myArray.size()) {
		myArray[i]->setPosition(x, y);
		if (myArray[i]->getString() != getName() && myArray[i]->getString() != _selectedGame) {
			myArray[i]->setFillColor(sf::Color::White);
			if (activeMouseOver)
			mouseHover(myArray[i], position);
		}
		else {
			if (activeMouseOver)
			myArray[i]->setFillColor(sf::Color::Red);
		}
		_myWindow->draw(*myArray[i]);
		y += myArray[i]->getCharacterSize() + 4;
		i++;
	}
}

sf::Text *SFMLDisplayModule::clickOnText(std::vector<sf::Text *> myArray)
{
	unsigned int i = 0;
	sf::Vector2i position = sf::Mouse::getPosition(*_myWindow);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		while (i < myArray.size()) {
			if (myArray[i]->getGlobalBounds().contains(position.x, position.y)) {
				return (myArray[i]);
			}
			i++;
		}
	}
	return (NULL);
}

int SFMLDisplayModule::detectClickMenu(sf::Vector2i position)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (play->_sprite.getGlobalBounds().contains(position.x, position.y)) {
			menuRun = 0;
			return (1);
		}
		if (scoreboard->_sprite.getGlobalBounds().contains(position.x, position.y)) {
			printScoreBoard(position);
		}
	}
	return (0);
}

void SFMLDisplayModule::detectUserTextInput(sf::Event event)
{
	static std::string str = "";

	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == 8) {
			if (!str.empty())
				str.pop_back();
			_SFMLUsername->setString(str);
		}
		else if (event.text.unicode > 31 && event.text.unicode < 128)
		{
			str += static_cast<char>(event.text.unicode);
			_SFMLUsername->setString(str);
		}
		if (str != "")
			this->setUserName(str);
	}

}

void SFMLDisplayModule::menuSpriteHover(sf::Vector2i position)
{
	play->setPosition(play->midX(640), play->midY(480) + 150);
	scoreboard->setPosition(scoreboard->midX(640), scoreboard->midY(480) + 178);
	if (play->_sprite.getGlobalBounds().contains(position.x, position.y)) {
		play->setPosition(play->_x - 2, play->_y - 2);
	}
	if (scoreboard->_sprite.getGlobalBounds().contains(position.x, position.y)) {
		scoreboard->setPosition(scoreboard->_x - 1, scoreboard->_y - 1);
	}
}

void SFMLDisplayModule::printScoreBoard(sf::Vector2i position)
{
	int z = 0;

	_myWindow->clear(sf::Color::Black);
	this->_coreProgram->pushScores();
	_myWindow->draw(background->_sprite);
	_myWindow->draw(scoreboard->_sprite);
	this->_SMFLScores = createSFMLTextArray(_scores, 14);
	printSFMLTextArray(this->_SMFLScores, 50, 50, 0);
	while (z == 0) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (scoreboard->_sprite.getGlobalBounds().contains(position.x, position.y)) {
				z = 1;
			}
		}
	}
}

void SFMLDisplayModule::drawEverything()
{
	_myWindow->clear(sf::Color::Black);
	_myWindow->draw(background->_sprite);
	_myWindow->draw(*_SFMLUsername);
	_myWindow->draw(*enterYourName);
	printSFMLTextArray(this->_SMFLGraphicLibName, 70, 160);
	printSFMLTextArray(this->_SMFLGameLibName, 380, 160);
	_myWindow->draw(title->_sprite);
	_myWindow->draw(changeLib->_sprite);
	_myWindow->draw(chooseGame->_sprite);
	_myWindow->draw(play->_sprite);
	_myWindow->draw(scoreboard->_sprite);
}

void SFMLDisplayModule::makeSelection()
{
	sf::Text *selection;
	std::string selectedLib;
	std::string selectedGame;

	selection = clickOnText(this->_SMFLGraphicLibName);
	if (selection)
	{
		selectedLib = selection->getString();
		if (selectedLib != "" && selectedLib != this->getName()) {
			menuRun = 0;
			this->_coreProgram->setGraphicLib(selectedLib);
		}
	}
	selection = clickOnText(this->_SMFLGameLibName);
	if (selection)
	{
		selectedGame = selection->getString();
		if (selectedGame != _selectedGame && selectedGame != "") {
			_selectedGame = selectedGame;
			this->_coreProgram->setGameLib(_selectedGame);
		}
	}
}

int SFMLDisplayModule::displayMenu()
{
	sf::Event event;
	sf::Font font;
	std::string buf;

	menuRun = 1;
	_selectedGame = this->_gameLibName[0];
	this->_coreProgram->setGameLib(_selectedGame);
	while (menuRun) {
		_myWindow->setActive();
		while (_myWindow->pollEvent(event))
		{
			detectUserTextInput(event);
			menuSpriteHover(sf::Mouse::getPosition(*_myWindow));
			makeSelection();
			if (event.type == sf::Event::Closed) {
				this->destroy();
				exit(0);
			}
		}
		drawEverything();
		if (detectClickMenu(sf::Mouse::getPosition(*_myWindow)))
			return (1);
		_myWindow->display();
		if (!menuRun)
			break;
	}
	return (0);
}

void SFMLDisplayModule::printText(std::string inputText, long timeout)
{
	sf::Text text;

	text.setFont(*_font);
	text.setCharacterSize(20);
	text.setPosition((_myWindow->getSize().x - (inputText.size()
			* text.getCharacterSize()))/ 2, _myWindow->getSize().y / 2);
	text.setString(inputText);
	_myWindow->clear(sf::Color::Black);
	_myWindow->draw(text);
	_myWindow->display();
	usleep(timeout);
}

void SFMLDisplayModule::setGraphicLibName(std::vector<std::string> graphicLibName)
{
	this->_graphicLibName = graphicLibName;
}

void SFMLDisplayModule::setGameLibName(std::vector<std::string> GameLibName)
{
	this->_gameLibName = GameLibName;
}

void SFMLDisplayModule::setScore(std::vector<std::string> scores)
{
	this->_scores = scores;
}

void SFMLDisplayModule::setUserName(std::string userName)
{
	this->_userName = userName;
}

void *SFMLDisplayModule::getHandler() const
{
	return (this->_handler);
}
