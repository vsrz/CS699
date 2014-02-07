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

sf::IntRect Tile::getTextureRect()
{
	sf::Vector2i realPos(mPosition.x * mTileSize.x, mPosition.y * mTileSize.y);
	return sf::IntRect(realPos, mTileSize);
}
