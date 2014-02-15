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
	
	sf::Vector2i getWorldSize();
	sf::Vector2i getTileSize();
	sf::IntRect getTextureRect(int x, int y, const char* layerName);
	sf::Vector2f getWorldPosition(int x, int y);
	sf::Sprite getSprite(int x, int y, const char* layerName);
	sf::Texture& getTexture(int x, int y, const char* layerName);
	int getTileNumber(int x, int y);

private:
	
	// tileset element of the xml node
	// keeping case consistent with the file format (no camelCase)
	struct Tileset
	{
		int id;
		int firstgid;
		std::string name;
		int tilewidth;
		int tileheight;
		sf::Texture texture;
		int imagewidth;
		int imageheight;
	};
	
	int getTilesetIndex(int gid);
	sf::Vector2i getTextureCoords(int x, int y, const char* layerName);

	// XML objects
	tinyxml2::XMLDocument mXmlDocument;
	tinyxml2::XMLElement* mXmlMapElement;
	tinyxml2::XMLElement* mXmlLayerElement;

	// Tileset
	std::vector<Tileset> mTileset;
	
	// Determines where the gid break is in each tileset
	std::vector<int> mTilesetFirstGids;

	// Map Width/Height is measured in tile units
	int mMapWidth;
	int mMapHeight;

	// Tile Width/Height is taken from the map node
	int mTileWidth;
	int mTileHeight;

	// Convert X Y to GID
	int getGid(int x, int y, const char* layerName);

};

#endif
