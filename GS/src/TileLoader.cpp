#include "TileLoader.h"
#include "Glob.h"
#include <iostream>

TileLoader::TileLoader(const char* filename)
{
	loadFromFile(filename);
}

sf::Vector2i TileLoader::getWorldSize()
{
	return sf::Vector2i(mMapWidth, mMapHeight);
}

sf::Vector2f TileLoader::getWorldPosition(int x, int y)
{
	return sf::Vector2f(static_cast<float>(x) * Config::TILE_WIDTH, static_cast<float>(y) * Config::TILE_HEIGHT);
}

void TileLoader::loadFromFile(const char* filename)
{

	// Returns 0 on success
	if (mXmlDocument.LoadFile(filename))
	{
		throw std::runtime_error("TileLoader: Failed to load tilemap data " + std::string(filename));
	}

	// Read map element
	mXmlMapElement = mXmlDocument.FirstChildElement("map")->ToElement();
	
	if (!mXmlMapElement)
	{
		throw std::runtime_error("Unable to load map element from XMLDocument");
	}
	mMapWidth = mXmlMapElement->IntAttribute("width");
	mMapHeight = mXmlMapElement->IntAttribute("height");

	// Get tile sizes
	mTileWidth = mXmlMapElement->IntAttribute("tilewidth");
	mTileHeight = mXmlMapElement->IntAttribute("tileheight");

	int id = 0;
	// Load tileset data
	tinyxml2::XMLElement* tileset = mXmlMapElement->FirstChildElement("tileset")->ToElement();
	for (tileset; tileset; tileset = tileset->NextSiblingElement("tileset"))
	{
		tinyxml2::XMLElement* imageElement = tileset->FirstChildElement("image")->ToElement();
		Tileset t;

		// Load tileset attributes
		t.id = id++;
		t.firstgid = tileset->IntAttribute("firstgid");
		t.tilewidth = tileset->IntAttribute("tilewidth");
		t.tileheight = tileset->IntAttribute("tileheight");
		t.name = tileset->Attribute("name");

		// Load image attributes
		// Only 1 image per tileset is supported
		t.texture.loadFromFile(std::string("res/") + imageElement->Attribute("source"));
		t.imagewidth = imageElement->IntAttribute("width");
		t.imageheight = imageElement->IntAttribute("height");

		mTilesetFirstGids.push_back(t.firstgid);
		mTileset.push_back(t);
	} 
}

// Returns a sprite given the X and Y coordinate of the item on the tilemap
sf::Sprite TileLoader::getSprite(int x, int y, const char* layerName)
{
	int tileNum = x + y * mMapWidth;
	int gid;
	bool found = false;

	// Load the data element from the matching layer
	tinyxml2::XMLElement* xmlLayerElement = 
		mXmlMapElement->FirstChildElement("layer");

	while (!found && xmlLayerElement != NULL)
	{
		if (xmlLayerElement->Attribute("name") == std::string(layerName))
		{
			found = true;
		}
	}

	if (xmlLayerElement == NULL)
	{
		throw std::runtime_error("TileLoader: No layer was found by the name " + std::string(layerName));
	}

	tinyxml2::XMLElement* xmlLayerDataElement = 
		xmlLayerElement->FirstChildElement("data");
	if (xmlLayerDataElement == NULL)
	{
		throw std::runtime_error("TileLoader: No data element was found in layer " + std::string(layerName));
	}

	tinyxml2::XMLElement* xmlTileElement = 
		xmlLayerDataElement->FirstChildElement("tile");

	if (xmlTileElement == NULL)
	{
		throw std::runtime_error("TileLoader: No tile element was found in layer " + std::string(layerName));
	}
	
	// Increment through the tilemap until you reach the correct tile element
	for(int tile = 0; tile < tileNum; tile++)
	{
		xmlTileElement = xmlLayerDataElement->NextSiblingElement("tile");
	}

	
	gid = xmlTileElement->IntAttribute("gid");

	for (auto iter = mTileset.begin(); 
		iter != mTileset.end(); ++iter)
	{
		if (iter->name == std::string(layerName))
		{
			// Square pointing to the location of the tile sub-texture
			sf::IntRect sp(x * iter->tilewidth, y * iter->tileheight, 
				iter->tilewidth, iter->tileheight);
			
			return sf::Sprite(iter->texture, sp);
		}

	}

	return sf::Sprite();

}

// Return the tile number based on X, Y coordinate
int TileLoader::getTileNumber(int x, int y)
{
	return x + y * mMapWidth;
}

// Return a reference to the texture given by the layer string
sf::Texture& TileLoader::getTexture(int x, int y, const char* layerName)
{
	int gid = getGid(x, y, layerName);
	return mTileset[getTilesetIndex(gid)].texture;
}

// Return the index number of the Tileset. This is useful when
// you just need to get some information when you've loaded multiple
// tilesets
int TileLoader::getTilesetIndex(int gid)
{
	if (gid == 0) return 0;
	int index = -1;
	int lo = 0, hi;
	for (std::vector<int>::iterator iter = mTilesetFirstGids.begin();
		iter != mTilesetFirstGids.end(); ++iter)
	{
		hi = *iter;
		if (gid >= lo && gid < hi)
		{
			return index;
		}
		index++;
		lo = hi;
	}
	return index;
}

// Get the coordinates of the texture from the gid
sf::Vector2i TileLoader::getTextureCoords(int x, int y, const char* layerName)
{
	int gid = getGid(x, y, layerName);
	int index = getTilesetIndex(gid);
	gid -= mTilesetFirstGids[index];
	int tilesetGridHeight = mTileset[index].imageheight / mTileset[index].tileheight;
	int tilesetGridWidth =  mTileset[index].imagewidth / mTileset[index].tilewidth;
	int gidx = (gid % tilesetGridWidth);
	int gidy = 0;
	while(gid > gidx)
	{
		gid = gid - tilesetGridWidth;
		gidy++;
	}
	return sf::Vector2i(gidx, gidy);
}

int TileLoader::getGid(int x, int y, const char* layerName)
{
	/* find the gid of the x,y passed */
	int tileNum = getTileNumber(x, y);
	bool found = false;

	// Load the data element from the matching layer
	tinyxml2::XMLElement* xmlLayerElement = 
		mXmlMapElement->FirstChildElement("layer");

	while (!found && xmlLayerElement != NULL)
	{
		if (xmlLayerElement->Attribute("name") == std::string(layerName))
		{
			found = true;
		}
		else
		{
			xmlLayerElement = xmlLayerElement->NextSibling()->ToElement();
		}
	}

	if (xmlLayerElement == NULL)
	{
		throw std::runtime_error("TileLoader: No layer was found by the name " + std::string(layerName));
	}

	tinyxml2::XMLElement* xmlLayerDataElement = 
		xmlLayerElement->FirstChildElement("data");
	if (xmlLayerDataElement == NULL)
	{
		throw std::runtime_error("TileLoader: No data element was found in layer " + std::string(layerName));
	}

	tinyxml2::XMLElement* xmlTileElement = 
		xmlLayerDataElement->FirstChildElement("tile");

	if (xmlTileElement == NULL)
	{
		throw std::runtime_error("TileLoader: No tile element was found in layer " + std::string(layerName));
	}
	
	// Increment through the tilemap until you reach the correct tile element
	for(int tile = 0; tile < tileNum; tile++)
	{
		xmlTileElement = xmlTileElement->NextSibling()->ToElement();
	}

	if (xmlTileElement == NULL)
	{
		throw std::runtime_error("TileLoader: No tile element was found in layer during search " + std::string(layerName));
	}
	
	return xmlTileElement->IntAttribute("gid");
	
}

sf::IntRect TileLoader::getTextureRect(int x, int y, const char* layerName)
{
	int gid = getGid(x, y, layerName);

	if (gid != 0)
	{
		sf::Vector2i coords = getTextureCoords(x, y, layerName);
		return sf::IntRect(coords.x * mTileWidth, coords.y *mTileHeight, mTileWidth, mTileHeight);
	}

	// No Texture
	return sf::IntRect(-1,-1,-1,-1);

}


sf::Vector2i TileLoader::getTileSize()
{
	return sf::Vector2i(mTileWidth, mTileHeight);
}
