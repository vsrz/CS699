#include "Tileset.h"


Tileset::Tileset(sf::Image& image, sf::Vector2i tileSize)
	: mImage(image)
	, mTileSize(tileSize)
{
}



Tileset::Tileset(sf::Image& image)
	: mImage(image)
	, mTileSize()
{
}

void Tileset::setImage(sf::Image& image)
{
	mImage = image;
}

void Tileset::setTileSize(sf::Vector2i tileSize)
{
	mTileSize = tileSize;
}