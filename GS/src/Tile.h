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
	sf::Vector2f getWorldPosition();
	sf::Vector2i getTileSize();

	void setWorldPosition(sf::Vector2f position);

private:
	// Tilemap that this tile is contained in
	sf::Texture& mTexture;

	// Size of each tile on the map, in pixels
	sf::Vector2i mTileSize;

	// Position on the tilemap
	sf::Vector2i mPosition;
	
	// Position of this tile in the world
	sf::Vector2f mWorldPosition;
};

#endif
