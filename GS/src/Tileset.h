#ifndef TILESET_H
#define TILESET_H

#pragma once

#include <SFML/Graphics.hpp>

class Tileset
{
public:
	Tileset(sf::Image& image, sf::Vector2i tileSize);
	Tileset(sf::Image& texture);
	Tileset(void);


	void setImage(sf::Image& image);
	void setTileSize(sf::Vector2i tileSize);

private:

	
	// Reference to the tilemap
	sf::Image& mImage;
	
	// The size of each tile in the Tileset
	sf::Vector2i mTileSize;


};

#endif
