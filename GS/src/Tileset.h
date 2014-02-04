#ifndef TILESET_H
#define TILESET_H

#pragma once

#include <SFML/Graphics.hpp>

class Tileset
{
public:
	Tileset(sf::Texture& texture);
	
private:
	sf::Texture& mTexture;
	sf::Vector2i mTileSize;


};

#endif
