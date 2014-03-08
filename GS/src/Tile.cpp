#include "Tile.h"


Tile::Tile()
	: mProperties(0)
{

}

// Set metadata for this tile
void Tile::setProperty(unsigned int property)
{
	mProperties |= property;
}

// Returns true if the tile is occupied by an object that may not be passed through
bool Tile::isOccupied()
{
	return (mProperties & Tiles::Property::Occupied);
}

bool Tile::isWaitingChair()
{
	return (mProperties & Tiles::Property::WaitingChair);
}

unsigned int Tile::getTileProperty()
{
	return mProperties;
}
