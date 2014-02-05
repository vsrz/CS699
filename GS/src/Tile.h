#ifndef TILE_H
#define TILE_H

#pragma once

#include <SFML/Graphics.hpp>
#include "Tileset.h"

class Tile
{
public:
	Tile(sf::Texture& texture);
	Tile(sf::Texture& texture, sf::Vector2i location);

private:
	sf::Sprite mSprite;
	sf::Vector2i mLocation;

};

#endif
