#include "Tile.h"


Tile::Tile()
	: mProperties(0)
{

}

// Set metadata for this tile
void Tile::setProperty(unsigned int property)
{
	mProperties += property;
}

// Returns true if you cannot pass through this tile
bool Tile::isBlocking()
{
	return (mProperties & Tiles::Property::Blocking);
}

