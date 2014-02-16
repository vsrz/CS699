#ifndef TILE_H
#define TILE_H

/**
 *	Tile.h
 *  Stores metadata about a specific tile on the map
 **/

#pragma once

#include <SFML/Graphics.hpp>

namespace Tiles
{
	enum Property
	{
		None = 0,
		Blocking = 1 << 0,
		Occupied = 1 << 1,
	};
};


class Tile 
{
public:
	Tile();
	
	void setProperty(unsigned int property);
	bool isBlocking();

private:
	unsigned int mProperties;

};

#endif
