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

class ChairEntity;

enum Direction
{
	None = 0,
	South = 1 << 1,
	North = 1 << 2,
	West = 1 << 3,
	East = 1 << 4,
};

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
		const std::array<TilePosition, 11u> STAGING_POSITION = 
		{
			TilePosition(3, 6),
			TilePosition(4, 7),
			TilePosition(4, 8),
			TilePosition(2, 7),
			TilePosition(2, 8),
			TilePosition(17, 8),
			TilePosition(17, 10),
			TilePosition(16, 6),
			TilePosition(18, 6),
			TilePosition(10, 9),
			TilePosition(12, 9),
		};

		// The position they actually wait at
		const std::array<TilePosition, 11u> SEATING_POSITION =
		{
			TilePosition(3, 5),
			TilePosition(5, 7),
			TilePosition(5, 8),
			TilePosition(1, 7),
			TilePosition(1, 8),
			TilePosition(18, 8),
			TilePosition(18, 10),
			TilePosition(16, 5),
			TilePosition(18, 5),
			TilePosition(10, 8),
			TilePosition(12, 8),
		};

		// The direction they are facing when they sit
		const std::array<Direction, 11u>	SEATING_DIRECTION =
		{
			Direction::South,
			Direction::West,
			Direction::West,
			Direction::East,
			Direction::East,
			Direction::West,
			Direction::West,
			Direction::South,
			Direction::South,
			Direction::South,
			Direction::South,
		};

		// The direction they are facing when they sit
		const std::array<unsigned int, 11u> TYPE =
		{
			0,
			0,
			0,
			0,
			0,
			1,
			1,
			2,
			2,
			3,
			3,
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
	pos.x = floor(pos.x);
	pos.y = floor(pos.y);
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

