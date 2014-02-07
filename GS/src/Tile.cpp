#include "Tile.h"


Tile::Tile(sf::Texture& texture, sf::Vector2i position, sf::Vector2i tileSize)
	: mTexture(texture)
	, mPosition(position)
	, mTileSize(tileSize)
{
}

sf::Texture& Tile::getTexture()
{
	return mTexture;
}

// Returns a rectangle of the square that the desired tile is located
sf::IntRect Tile::getTextureRect()
{
	sf::Vector2i realPos(mPosition.x * mTileSize.x, mPosition.y * mTileSize.y);
	return sf::IntRect(realPos, mTileSize);
}

sf::Vector2f Tile::getWorldPosition()
{	
	return mWorldPosition;
}

void Tile::setWorldPosition(sf::Vector2f position)
{
	mWorldPosition = position;
}

sf::Vector2i Tile::getTileSize()
{
	return mTileSize;
}