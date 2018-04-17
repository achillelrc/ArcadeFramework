//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// SFMLDisplayModule.hpp
//

#ifndef SFMLDISPLAYMODULE_HPP_
# define SFMLDISPLAYMODULE_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "Error.hpp"

class SFMLSprite {
public:
	~SFMLSprite() = default;

	void setPosition(double x, double y)
	{
		_x = x;
		_y = y;
		_sprite.setPosition(_x, _y);
	}

	double midX(double x) const
	{
		return ((x / 2.0) - (_imageSize.x / 2.0));
	}

	double midY(double y) const
	{
		return ((y / 2.0) - (_imageSize.y / 2.0));
	}

	void update()
	{
		_texture.update(_pixels);
	}

	SFMLSprite(std::string path, double x, double y) : _x(x), _y(y)
	{
		if (!_texture.loadFromFile(path))
		{
			throw Handler("SFML Lib", "cannot load sprite " + path);
		}
		_imageSize = _texture.getSize();
		_texture.setSmooth(true);
		_texture.setRepeated(false);
		_pixels = new sf::Uint8[_imageSize.x * _imageSize.y * 4];
		update();
		_sprite.setTexture(_texture);
		_sprite.setPosition(_x, _y);
	}

	sf::Sprite _sprite;
	double _x;
	double _y;
private:
	sf::Texture _texture;
	sf::Uint8* _pixels;
	sf::Vector2u _imageSize;
};

class SFMLTileMap : public sf::Drawable, public sf::Transformable
{
public:

	void setGameMap(std::vector<std::string> gameMap)
	{
		this->_gameMap = gameMap;
	}

	void updateObj(IGameModule *game, sf::RenderWindow *myWindow, sf::Vector2u tileSize)
	{
		unsigned int i = 0;
		std::vector<objPos_t> objMap = game->getObjPos();
		std::map<char, std::pair<int, int>> tilemap = game->getTilemap()->getTilemap();
		int offset = myWindow->getSize().x / 2 - (game->getMapSize().second * game->getTilemap()->getScale()) / 2;
		char tileValue;

		while (i < objMap.size()) {
			sf::VertexArray quad(sf::Quads, 4);

			tileValue = objMap[i].value;
			quad[0].position = sf::Vector2f(objMap[i].x * tileSize.x + offset, objMap[i].y * tileSize.y);
			quad[1].position = sf::Vector2f((objMap[i].x + 1) * tileSize.x + offset, objMap[i].y * tileSize.y);
			quad[2].position = sf::Vector2f((objMap[i].x + 1) * tileSize.x + offset, (objMap[i].y + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(objMap[i].x * tileSize.x + offset, (objMap[i].y + 1) * tileSize.y);
			quad[0].texCoords = sf::Vector2f(tilemap[tileValue].first, tilemap[tileValue].second);
			quad[1].texCoords = sf::Vector2f(tilemap[tileValue].first + tileSize.x, tilemap[tileValue].second);
			quad[2].texCoords = sf::Vector2f(tilemap[tileValue].first + tileSize.x,  tilemap[tileValue].second + tileSize.y);
			quad[3].texCoords = sf::Vector2f(tilemap[tileValue].first, tilemap[tileValue].second + tileSize.y);
			myWindow->draw(quad, &m_tileset);
			i++;
		}
	}

	bool load(const std::string& tileset, sf::Vector2u tileSize, IGameModule *currentGame)
	{
		sf::Image img;
		sf::Color offcolor;
		unsigned int width = currentGame->getMapSize().first;
		unsigned int height = currentGame->getMapSize().second;
		std::map<char, std::pair<int, int>> tilemap = currentGame->getTilemap()->getTilemap();

		if (!img.loadFromFile(tileset)) {
			return false;
		}
		offcolor = img.getPixel(0, 0);
		img.createMaskFromColor(offcolor);
		if (!m_tileset.loadFromImage(img)) {
			return false;
		}
		m_tileset.setSmooth(1);
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);
		for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			char tileValue = _gameMap[j][i];
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
			quad[0].texCoords = sf::Vector2f(tilemap[tileValue].first, tilemap[tileValue].second);
			quad[1].texCoords = sf::Vector2f(tilemap[tileValue].first + tileSize.x, tilemap[tileValue].second);
			quad[2].texCoords = sf::Vector2f(tilemap[tileValue].first + tileSize.x,  tilemap[tileValue].second + tileSize.y);
			quad[3].texCoords = sf::Vector2f(tilemap[tileValue].first, tilemap[tileValue].second + tileSize.y);
		}
		return true;
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &m_tileset;
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	std::vector<std::string> _gameMap;
};

class SFMLDisplayModule : public IDisplayModule {
public:
	SFMLDisplayModule();
	~SFMLDisplayModule();
	void init(ICoreProgram *);
	void setHandler(void *);
	void *getHandler() const;
	void updateDisplay(IGameModule *);
	void destroy();
	std::string getKey();
	void keyAction(std::string);
	const std::string &getName() const;
	const std::string &getUserName() const;
	int displayMenu();
	void printText(std::string, long);
	void setGraphicLibName(std::vector<std::string>);
	void setGameLibName(std::vector<std::string>);
	void setScore(std::vector<std::string>);
	void setUserName(std::string userName);
	std::vector<sf::Text *> createSFMLTextArray(std::vector<std::string> text, int size);
	void printSFMLTextArray(std::vector<sf::Text *> myArray, double, double, bool = 1);
	sf::Text *clickOnText(std::vector<sf::Text *> myArray);
	std::string detectKey();
	void initMenuAction();
	std::string getMenuAction(std::string str);
	void detectUserTextInput(sf::Event);
	void menuSpriteHover(sf::Vector2i position);
	void printScoreBoard(sf::Vector2i position);
	void drawEverything();
	int detectClickMenu(sf::Vector2i position);
	void makeSelection();
private:
	std::string _name;
	std::string _userName;
	sf::RenderWindow *_myWindow;
	void *_handler;
	ICoreProgram *_coreProgram;
	std::vector<std::string> _graphicLibName;
	std::vector<std::string> _gameLibName;
	std::vector<std::string> _scores;
	SFMLSprite *background;
	SFMLSprite *title;
	SFMLSprite *changeLib;
	SFMLSprite *chooseGame;
	SFMLSprite *play;
	SFMLSprite *scoreboard;
	std::vector<sf::Text *> _SMFLGraphicLibName;
	std::vector<sf::Text *> _SMFLScores;
	std::vector<sf::Text *> _SMFLGameLibName;
	std::vector<sf::Text *> _rules;
	sf::Font *_font;
	sf::Text *enterYourName;
	sf::Text *_SFMLUsername;
	int menuRun;
	std::string _selectedGame;
	std::map<std::string, std::string> _menuAction;
};

#endif // SFMLDISPLAYMODULE_HPP_
