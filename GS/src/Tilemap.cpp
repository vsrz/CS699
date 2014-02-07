#include "Tilemap.h"


Tilemap::Tilemap(const char* filename)
{
	loadTilemap(filename);
}

void Tilemap::loadTilemap(const char* filename)
{
	if (!mDocument.LoadFile(filename))
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
}


/**
 *	Since we're loading the tileset outside of this class
 *	we'll require the name of the layer to extract the tile
 *	ID from in order to return the IntRect that will be needed
 *	to pull the correct tile
 **/
sf::IntRect Tilemap::getTextureRect()
{
	
	return sf::IntRect();
}


sf::Vector2i Tilemap::getTileSize()
{
	return sf::Vector2i(mTileWidth, mTileHeight);
}
