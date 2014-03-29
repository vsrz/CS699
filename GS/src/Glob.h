#ifndef GLOB_H
#define GLOB_H


#include <array>
#include <map>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

typedef sf::Vector2i MousePosition;
typedef sf::Vector2f TilePosition;
typedef sf::Vector2f SpritePosition;

/* Dirty global configuration area, for now (forever?) */
namespace Config
{
	// Manager (PC) Config
	const float								MANAGER_SPEED = 5.f;
	const float								MIDAGE_MAN_SPEED = 3.f;

	// World Config
	const float								WORLD_WIDTH	= 20.f;
	const float								WORLD_HEIGHT = 12.f;
	const float								WORLD_SCALE = 2.f;
	
	// Tiles
	const char*	const						TILEMAP_FILENAME = "res/Tilemap.tmx";		
	const float								TILE_WIDTH = 32.f;
	const float								TILE_HEIGHT = 32.f;

	// Pathfinder
	const int								MAX_SEARCH = 500;

	// Waiting room chairs
	namespace Chairs
	{
		// The position they move to before sitting
		const std::array<TilePosition, 5>	WAITING_CHAIR_POSITIONS = 
		{
			TilePosition(3, 6),
			TilePosition(4, 7),
			TilePosition(4, 8),
			TilePosition(2, 7),
			TilePosition(2, 8),

		};

		// The position they actually wait at
		const std::array<TilePosition, 5>	WAITING_CHAIR_SEATS =
		{
			TilePosition(3, 5),
			TilePosition(5, 7),
			TilePosition(5, 8),
			TilePosition(1, 7),
			TilePosition(1, 8),
		};
	}

	namespace Customer
	{
		// Amount of time in seconds to wait between customer arrivals
		const float							RELEASE_INTERVAL = 5.f;
	};
	
}

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

template<typename T>
void centerOrigin(T& obj)
{
	sf::FloatRect bounds = obj.getLocalBounds();
	obj.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

template<typename T>
sf::Vector2i toVector2i(T v)
{
	return sf::Vector2i(
		static_cast<int>(v.x),
		static_cast<int>(v.y));
}

template<typename T>
sf::Vector2f toVector2f(T v)
{
	return sf::Vector2f(
		static_cast<int>(v.x),
		static_cast<int>(v.y));
}

// Get the X,Y coordinate of a tile given a pixel
template<typename T>
TilePosition toTilePosition(T pixelPosition)
{
	sf::Vector2f pos = snapToSpritePosition(pixelPosition);
	pos.x = pixelPosition.x / (Config::TILE_WIDTH * Config::WORLD_SCALE);
	pos.y = pixelPosition.y / (Config::TILE_HEIGHT * Config::WORLD_SCALE);
	return pos;
}

// Given a pixel on the screen, snap to the tile grid, returning the pixel in 
// the top left corner of the corresponding tile
template<typename T>
SpritePosition snapToSpritePosition(T pixelPosition)
{
	SpritePosition pos;
	for (float y = 0.f; 
		y <		Config::TILE_HEIGHT * Config::WORLD_HEIGHT * Config::WORLD_SCALE; 
		y +=	Config::TILE_HEIGHT * Config::WORLD_SCALE)	
	{
		for (float x = 0.f; 
				x <		Config::TILE_WIDTH * Config::WORLD_WIDTH * Config::WORLD_SCALE; 
				x +=	Config::TILE_WIDTH* Config::WORLD_SCALE)
		{			
			if (pixelPosition.x >= x)
				pos.x = x;
			if (pixelPosition.y >= y)
				pos.y = y;
			
		}
	}
	return pos;
}

// Get the pixel at the top left corner of a tile given a tile position
template<typename T>
SpritePosition toSpritePosition(T tilePosition)
{
	SpritePosition pos;
	
	pos.x = tilePosition.x * Config::TILE_WIDTH * Config::WORLD_SCALE;
	pos.y = tilePosition.y * Config::TILE_HEIGHT * Config::WORLD_SCALE;
	return snapToSpritePosition(pos);
}

#endif

