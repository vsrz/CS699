#include "Tilemap.h"
#include <iostream>

Tilemap::Tilemap(const char* filename)
{
	loadTilemap(filename);
}

void Tilemap::loadTilemap(const char* filename)
{

	// Returns 0 on success
	if (mDocument.LoadFile(filename))
	{
		throw std::runtime_error("Tilemap: Failed to load tilemap data " + std::string(filename));
	}

	// Read map element
	mMapElement = mDocument.FirstChildElement("map")->ToElement();
	
	if (!mMapElement)
	{
		throw std::runtime_error("Unable to load map element from XMLDocument");
	}
	mMapWidth = mMapElement->IntAttribute("width");
	mMapHeight = mMapElement->IntAttribute("height");

	// Get tile sizes
	mTileWidth = mMapElement->IntAttribute("tilewidth");
	mTileHeight = mMapElement->IntAttribute("tileheight");

	// Load tileset data
	
}


sf::IntRect Tilemap::getTextureRect()
{
	
	return sf::IntRect();
}


sf::Vector2i Tilemap::getTileSize()
{
	return sf::Vector2i(mTileWidth, mTileHeight);
}
