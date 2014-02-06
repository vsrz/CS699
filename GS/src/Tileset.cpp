#include "Tileset.h"


Tileset::Tileset(sf::Texture& tileset, sf::Vector2i tileSize)
	: mTileset(tileset)
	, mTileSize(tileSize)
{
}

sf::Sprite Tileset::getSprite()
{
	return sf::Sprite(mTileset, sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(16,16)));
}

Tileset::Tileset(sf::Texture& tileset)
	: mTileset(tileset)
	, mTileSize()
{
}

void Tileset::setTileSize(sf::Vector2i tileSize)
{
	mTileSize = tileSize;
}

void Tileset::setTileCount(int width, int height)
{
	mTileCount.x = width;
	mTileCount.y = height;
}
