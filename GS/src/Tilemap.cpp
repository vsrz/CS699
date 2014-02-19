#include "TileMap.h"
#include <stdexcept>

Tilemap::Tilemap(int worldTileWidth, int worldTileHeight, 
				 int tileWidth, int tileHeight, int worldScale)
	: mWorldWidth(worldTileWidth)
	, mWorldHeight(worldTileHeight)
	, mWorldScale(worldScale)
	, mTileWidth(tileWidth)
	, mTileHeight(tileHeight)
{

}

// set the property of a specific tile on the map
void Tilemap::setTileProperty(int x, int y, unsigned int tileProperty)
{
	mTiles[toTileNumber(x, y)].setProperty(tileProperty);
}

/* Given a tile coordinate, return the pixel position of the top left 
 corner of the tile relative to the window */
sf::Vector2f Tilemap::getTilePixelPosition(int x, int y)
{
	return sf::Vector2f(
		x * mWorldScale * mTileWidth,
		y * mWorldScale * mTileHeight
		);
}

bool Tilemap::isTileOccupied(int x, int y)
{
	return mTiles[toTileNumber(x,y)].isOccupied();
}

bool Tilemap::isTileOccupied(sf::Vector2i screenPosition)
{
	return mTiles[toTileNumber(screenPosition)].isOccupied();

}

bool Tilemap::isTileOccupied(sf::Vector2f screenPosition)
{
	return mTiles[toTileNumber(screenPosition)].isOccupied();

}

int Tilemap::toTileNumber(sf::Vector2i screenPosition)
{
	return toTileNumber(
		screenPosition.x / (mTileWidth * mWorldScale), 
		screenPosition.y / (mTileHeight * mWorldScale)
	);
}

int Tilemap::toTileNumber(sf::Vector2f screenPosition)
{
	return toTileNumber(
		sf::Vector2i(
			static_cast<int>(screenPosition.x),
			static_cast<int>(screenPosition.y)
			)
		);
}

int Tilemap::toTileNumber(int x, int y)
{
	int tileNum = x + mWorldWidth * y;
	
	// Throw error if tile is outside the world size
	if (tileNum > 239 || tileNum  < 0)
	{
		throw std::runtime_error("Tilemap: Tile Coordinates " 
			+ std::to_string(x) + "," + std::to_string(y) + " -> " 
			+ std::to_string(tileNum) + " out of range");
	}

	return tileNum;
}

