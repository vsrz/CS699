#ifndef TILE_H
#define TILE_H

#pragma once

#include <SFML/Graphics.hpp>
#include "Tileset.h"

class Tile
{
public:
	Tile(sf::Sprite& sprite, sf::Vector2f position);
	void draw(sf::RenderWindow& window);
private:
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	
};

#endif
