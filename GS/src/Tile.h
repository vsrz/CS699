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
		WaitingChair = 2 << 0,
		HasActor = 3 << 0,
	};
};


class Tile 
{
public:
	Tile();
	
	void setProperty(unsigned int property);
	void unsetProperty(unsigned int property);
	bool isOccupied();
	bool isWaitingChair();
	bool hasActor();

	unsigned int getTileProperty();

private:
	unsigned int mProperties;

};

#endif
