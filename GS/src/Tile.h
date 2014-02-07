#ifndef TILE_H
#define TILE_H

/**
 *	Tile.h
 *	Takes a texture and adapts it for use as a tilemap
 **/

#pragma once

#include <SFML/Graphics.hpp>


class Tile 
{
public:
	Tile(sf::Texture& texture, sf::Vector2i position, sf::Vector2i tileSize);
	sf::Texture& getTexture();
	sf::IntRect getTextureRect();

private:
	// Tilemap that this tile is contained in
	sf::Texture& mTexture;

	// Size of each tile on the map, in pixels
	sf::Vector2i mTileSize;

	// Position on the tilemap
	sf::Vector2i mPosition;
	
};

#endif
