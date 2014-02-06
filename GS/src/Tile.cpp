#include "Tile.h"


Tile::Tile(sf::Sprite& sprite, sf::Vector2f position)
	: mSprite(sprite)
	, mPosition(position)
{
	mSprite.setPosition(position);
}

void Tile::draw(sf::RenderWindow &window)
{
	window.draw(mSprite);
}
