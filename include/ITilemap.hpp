//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ITilemap.hpp
//

#ifndef ITILEMAP_HPP_
# define ITILEMAP_HPP_

#include <map>

class ITilemap{
public:
	virtual ~ITilemap() = default;
	virtual int getScale() const = 0;
	virtual std::map<char, std::pair<int, int>> getTilemap() const = 0;
	virtual std::string getTilemapPath() const = 0;
};

#endif // ITILEMAP_HPP_
