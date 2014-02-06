#ifndef TILESET_H
#define TILESET_H

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>

class Tileset
{
public:

	Tileset(sf::Texture& tileset, sf::Vector2i tileSize);
	Tileset(sf::Texture& tileset);
	Tileset(void);

	void setTileSize(sf::Vector2i tileSize);
	void setTileCount(int width, int height);
	sf::Sprite getSprite();

private:	

	// Reference to the tilemap
	sf::Texture mTileset;
	
	// The size of each tile in the Tileset
	sf::Vector2i mTileSize;

	// Height and width of the Tilemap
	sf::Vector2i mTileCount;

};

#endif
