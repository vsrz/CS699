#include "Tile.h"


Tile::Tile(sf::Texture& texture)
	: mLocation(0,0)
{
	mSprite.setTexture(texture);
}

Tile::Tile(sf::Texture& texture, sf::Vector2i location)
	: mLocation(location)
{
	mSprite.setTexture(texture);
}

