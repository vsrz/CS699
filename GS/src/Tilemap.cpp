#include "Tilemap.h"
#include <iostream>

Tilemap::Tilemap(const char* filename)
{
	loadTilemap(filename);
}

sf::Vector2i Tilemap::getWorldSize()
{
	return sf::Vector2i(mMapWidth, mMapHeight);
}

sf::Vector2f Tilemap::getWorldPosition(int x, int y)
{
	return sf::Vector2f(static_cast<float>(x) * 32.f, static_cast<float>(y) * 32.f);
}

void Tilemap::loadTilemap(const char* filename)
{

	// Returns 0 on success
	if (mXmlDocument.LoadFile(filename))
	{
		throw std::runtime_error("Tilemap: Failed to load tilemap data " + std::string(filename));
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
sf::Sprite Tilemap::getSprite(int x, int y, const char* layerName)
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
		throw std::runtime_error("Tilemap: No layer was found by the name " + std::string(layerName));
	}

	tinyxml2::XMLElement* xmlLayerDataElement = 
		xmlLayerElement->FirstChildElement("data");
	if (xmlLayerDataElement == NULL)
	{
		throw std::runtime_error("Tilemap: No data element was found in layer " + std::string(layerName));
	}

	tinyxml2::XMLElement* xmlTileElement = 
		xmlLayerDataElement->FirstChildElement("tile");

	if (xmlTileElement == NULL)
	{
		throw std::runtime_error("Tilemap: No tile element was found in layer " + std::string(layerName));
	}
	
	// Increment through the tilemap until you reach the correct tile element
	for(int tile = 0; tile < tileNum; tile++)
	{
		xmlTileElement = xmlLayerDataElement->NextSiblingElement("tile");
	}

	
	gid = xmlTileElement->IntAttribute("gid");

	for (std::vector<Tileset>::iterator iter = mTileset.begin(); 
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

sf::Texture& Tilemap::getTexture(const char* layerName)
{
	return mTileset[getTilesetIndex(layerName)].texture;
}

int Tilemap::getTilesetIndex(const char* layerName)
{
	int x = 0;
	for (std::vector<Tileset>::iterator iter = mTileset.begin(); 
		iter != mTileset.end(); ++iter)
	{
		if (iter->name == std::string(layerName))
		{
			
			return x++;
		}

	}
	return 0;
}

// Get the coordinates of the texture from the gid
sf::Vector2i Tilemap::getTextureCoords(int gid, const char* layerName)
{
	int index = getTilesetIndex(layerName);
	int tilesetGridHeight = mTileset[index].imageheight / mTileset[index].tileheight;
	int tilesetGridWidth =  mTileset[index].imagewidth / mTileset[index].tilewidth;
	int gidx = (gid % tilesetGridWidth)-1;
	int gidy = 0;
	while(gid-1 > gidx)
	{
		gid = gid - tilesetGridWidth;
		gidy++;
	}
	return sf::Vector2i(gidx, gidy);
}


sf::IntRect Tilemap::getTextureRect(int x, int y, const char* layerName)
{
	/* find the gid of the x,y passed */
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
		else
		{
			xmlLayerElement = xmlLayerElement->NextSibling()->ToElement();
		}
	}

	if (xmlLayerElement == NULL)
	{
		throw std::runtime_error("Tilemap: No layer was found by the name " + std::string(layerName));
	}

	tinyxml2::XMLElement* xmlLayerDataElement = 
		xmlLayerElement->FirstChildElement("data");
	if (xmlLayerDataElement == NULL)
	{
		throw std::runtime_error("Tilemap: No data element was found in layer " + std::string(layerName));
	}

	tinyxml2::XMLElement* xmlTileElement = 
		xmlLayerDataElement->FirstChildElement("tile");

	if (xmlTileElement == NULL)
	{
		throw std::runtime_error("Tilemap: No tile element was found in layer " + std::string(layerName));
	}
	
	// Increment through the tilemap until you reach the correct tile element
	for(int tile = 0; tile < tileNum; tile++)
	{
		xmlTileElement = xmlTileElement->NextSibling()->ToElement();
	}

	if (xmlTileElement == NULL)
	{
		throw std::runtime_error("Tilemap: No tile element was found in layer during search " + std::string(layerName));
	}
	
	gid = xmlTileElement->IntAttribute("gid");
	sf::Vector2i coords = getTextureCoords(gid, layerName);
	return sf::IntRect(coords.x * mTileWidth, coords.y *mTileHeight, mTileWidth, mTileHeight);
}


sf::Vector2i Tilemap::getTileSize()
{
	return sf::Vector2i(mTileWidth, mTileHeight);
}
