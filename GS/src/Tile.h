/**
 *	Tile.h
 *  Stores metadata about a specific tile on the map
 **/

#ifndef TILE_H
#define TILE_H

#pragma once

namespace Tiles
{
	enum Property
	{
		None = 0,
		Occupied = 1 << 0,
	};
};


class Tile 
{
public:
	Tile();
	
	void setProperty(unsigned int property);
	bool isOccupied();

private:
	unsigned int mProperties;

};

#endif
