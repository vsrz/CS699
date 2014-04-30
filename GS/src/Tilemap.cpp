#include "TileMap.h"
#include <stdexcept>

Tilemap::Tilemap(int worldTileWidth, int worldTileHeight, 
				 float tileWidth, float tileHeight, float worldScale)
	: mWorldWidth(worldTileWidth)
	, mWorldHeight(worldTileHeight)
	, mWorldScale(static_cast<int>(worldScale))
	, mTileWidth(static_cast<int>(tileWidth))
	, mTileHeight(static_cast<int>(tileHeight))
{

}

// Get tile number 
Tile* Tilemap::getTile(int x, int y)
{
	if (x < 0 || y < 0 || x > 19 || y > 11)
	{
		return nullptr;
	}
	return &mTiles[toTileNumber(x, y)];
	
}

unsigned int Tilemap::getTileProperty(int x, int y)
{
	return mTiles[toTileNumber(x, y)].getTileProperty();
}


unsigned int Tilemap::getTileProperty(TilePosition screenPosition)
{
	return mTiles[toTileNumber(screenPosition)].getTileProperty();
}

// set the property of a specific tile on the map
void Tilemap::setTileProperty(int x, int y, unsigned int tileProperty)
{
	mTiles[toTileNumber(x, y)].setProperty(tileProperty);
}

void Tilemap::unsetTileProperty(int x, int y, unsigned int tileProperty)
{
	mTiles[toTileNumber(x, y)].unsetProperty(tileProperty);
}

/* Given a tile coordinate, return the pixel position of the top left 
 corner of the tile relative to the window */
sf::Vector2f Tilemap::getTilePixelPosition(int x, int y)
{
	return sf::Vector2f(
			static_cast<float>(x * mWorldScale * mTileWidth),
			static_cast<float>(y * mWorldScale * mTileHeight)
		);
}

bool Tilemap::isTileOccupied(int x, int y)
{
	return mTiles[toTileNumber(x,y)].isOccupied();
}

bool Tilemap::isValidTile(TilePosition tile)
{
	return static_cast<size_t>(toTileNumber(tile)) <= mTiles.size();
}

bool Tilemap::isTileOccupied(TilePosition screenPosition)
{
	TilePosition pos;
	pos.x = floor(screenPosition.x);
	pos.y = floor(screenPosition.y);
	return mTiles[toTileNumber(pos)].isOccupied();

}


template<typename T>
bool Tilemap::isWaitingChair(T screenPosition)
{
	return mTiles[toTileNumber(T)].isWaitingChair();
}


int Tilemap::toTileNumber(TilePosition screenPosition)
{
	int x = static_cast<int>(floor(screenPosition.x));
	int y = static_cast<int>(floor(screenPosition.y));

	return toTileNumber(
		x / (mTileWidth * mWorldScale), 
		y / (mTileHeight * mWorldScale)
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

