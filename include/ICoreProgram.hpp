//
// EPITECH PROJECT, 2018
// bootstrap-arcade
// File description:
// ICoreProgram.hpp
//

#ifndef ICOREPROGRAM_HPP_
# define ICOREPROGRAM_HPP_

#include <string>
#include <vector>

class ICoreProgram {
public:
	virtual ~ICoreProgram() = default;
	virtual void setGraphicLib(const std::string &) = 0;
	virtual void setGameLib(const std::string &) = 0;
	virtual void pushGraphicName() = 0;
	virtual void pushGameName() = 0;
	virtual void pushScores() = 0;
	virtual void nextGraphicLib() = 0;
	virtual void nextGameLib() = 0;
	virtual void prevGraphicLib() = 0;
	virtual void prevGameLib() = 0;
	virtual void run() = 0;
};

#endif // ICOREPROGRAM_HPP_
