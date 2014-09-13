#ifndef GLOB_H
#define GLOB_H


#include <array>
#include <map>
#include <sstream>
#include <cmath>
#include <memory>
#include <vector>
#include <queue>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

typedef sf::Vector2i MousePosition;
typedef sf::Vector2f TilePosition;
typedef sf::Vector2f SpritePosition;

class ChairEntity;
class IndicatorEntity;

enum Direction
{
	None,
	South,
	North,
	West,
	East,
};

/* Dirty global configuration area, for now (forever?) */
namespace Config
{
	// Release string
	const std::string						RELEASE_STRING = "Build v0.5.0818.31";

	// Manager (PC) Config
	const float								MANAGER_SPEED = 5.f;

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

	// Tile you move to when leaving the scene
	const TilePosition						EXIT_TILE = TilePosition(7,0);

	// Maximum number of possible customers
	const int								MAXIMUM_CUSTOMERS = 50;

	// Indicator arrows (in seconds)
	const float								INDICATOR_ARROW_DURATION = 1.5f;
	const float								INDICATOR_ARROW_SPEED = 5.5f;
	// Waiting room chairs
	namespace Chairs
	{
		const int SIZE = 11u;

		// The position they move to before sitting
		const std::array<TilePosition, SIZE> STAGING_POSITION = 
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
		const std::array<TilePosition, SIZE> SEATING_POSITION =
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
		const std::array<Direction, SIZE>	SEATING_DIRECTION =
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


		/** 
		 *	The type of chair this is
		 *  0 for waiting
		 *	1 for washing
		 *	2 for cutting
		 *	3 for color
		 **/
		const std::array<unsigned int, SIZE> TYPE =
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

		// The position you need to be standing in order to operate the chair
		// We don't operate on waiting room chairs, so those are defaulted
		const std::array<TilePosition, SIZE> OPERATING_POSITION =
		{
			TilePosition(0,0),
			TilePosition(0,0),
			TilePosition(0,0),
			TilePosition(0,0),
			TilePosition(0,0),
			TilePosition(18,7),
			TilePosition(18,9),
			TilePosition(15,5),
			TilePosition(19,5),
			TilePosition(10,9),
			TilePosition(12,9),
		};

	}

	namespace RegisterQueue
	{
		// Size of the queue
		const size_t SIZE = 15;

		const std::array<TilePosition, SIZE> POSITION =
		{
			TilePosition(9,4),
			TilePosition(9,5),
			TilePosition(9,6),
			TilePosition(9,7),
			TilePosition(8,7),
			TilePosition(7,7),
			TilePosition(6,7),
			TilePosition(6,8),
			TilePosition(6,9),
			TilePosition(6,10),
			TilePosition(5,10),
			TilePosition(4,10),
			TilePosition(3,10),
			TilePosition(2,10),

		};

		// The direction they will stand when they are in a specific part of the line
		const std::array<Direction, SIZE> DIRECTION =
		{
			Direction::East,
			Direction::East,
			Direction::North,
			Direction::North,
			Direction::East,
			Direction::North,
			Direction::North,
			Direction::North,
			Direction::North,
			Direction::North,
			Direction::North,
			Direction::East,
			Direction::East,
			Direction::East,
			Direction::East,
		};

		// The spot you need to be standing in order to use the register
		// There's only 1 register to operate, so there's only one spot
		const std::array<TilePosition,1u> OPERATING_POSITION = 
		{ 
			TilePosition(11,4), 
		};

		// We're going to have two register positions since the art
		// looks a little awkward
		const std::array<TilePosition,2u> REGISTER_POSITION =
		{
			TilePosition(10,3),
			TilePosition(10,4),
		};
		
		
	};

	namespace Customer
	{
		// The position the sprite is placed when they are introduced into the scene
		const TilePosition					SPAWN_POSITION = TilePosition(7.f, 0.f);
		
		// The adjustment needed to draw the sprite on the tile they consume since
		// each sprite is actually two tiles in height
		const float							BASE_SPRITE_ORIGIN_X = 0.f;
		const float							BASE_SPRITE_ORIGIN_Y = 32.f;

		// The starting offset of the sprite
		const sf::Vector2i					SPRITE_ANIM_OFFSET(0,0);

		// The size of each frame
		const sf::Vector2i					SPRITE_ANIM_FRAME_SIZE(32, 64);

	};

	namespace Pet
	{
		const TilePosition					SPAWN_POSITION = TilePosition(8,8);
		const sf::Vector2i					SPRITE_ANIM_OFFSET(0,0);
		const sf::Vector2i					SPRITE_ANIM_FRAME_SIZE(32, 64);
		const float							SPRITE_ORIGIN_X = 0.f;
		const float							SPRITE_ORIGIN_Y = 32.f;
		const std::array<TilePosition, 2u>  SLEEP_TILE = 
		{
			TilePosition(0,4),
			TilePosition(9,3),
		};

	}
	
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

template<typename T>
float rndTenth(T val)
{
	return (float)(floor(val * 10 + 0.5) / 10.f);
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

typedef std::vector<std::unique_ptr<ChairEntity>> Chairs;
typedef std::vector<std::unique_ptr<IndicatorEntity>> ChairIndicators;

#endif

