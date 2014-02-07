/**
 *	Tilemap.h
 *	Loads tilemap data from a TMX file. Maps the gid given by
 *	the mapfile to the texture position in the loaded image.
 *	
 *	Definitions
 *	Tilemap		- The map file, TMX
 *	Tileset		- Image used to generate tiles
 *	Tile		- A portion of the image that is cut to form a tile
 *	
 *	See mapeditor.org for TMX file information.
 **/

#ifndef TILEMAP_H
#define TILEMAP_H

#pragma once

#include "TinyXML2/tinyxml2.h"
#include "Tile.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <array>

class Tilemap
{
public:
	Tilemap(const char* filename);
	Tilemap(void){}
	void loadTilemap(const char* filename);
	sf::Vector2i getTileSize();
	sf::IntRect getTextureRect();

private:
	// XML objects
	tinyxml2::XMLDocument mDocument;
	tinyxml2::XMLElement* mMapElement;
	tinyxml2::XMLElement* mLayerElement;

	// Textures
	std::vector<sf::Texture> mTextures;

	// Map Width/Height is measured in tile units
	int mMapWidth;
	int mMapHeight;

	// Tile Width/Height is taken from the map node
	int mTileWidth;
	int mTileHeight;

};

#endif
