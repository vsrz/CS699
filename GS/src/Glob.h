#ifndef GLOB_H
#define GLOB_H


#include <array>
#include <map>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

typedef sf::Vector2i Tilepos;
typedef sf::Vector2i MousePos;
typedef sf::Vector2f SpritePos;

/* Dirty global configuration area, for now (forever?) */
namespace Config
{
	// Manager (PC) Config
	const float								MANAGER_SPEED = 5.f;
	const float								MIDAGE_MAN_SPEED = 3.f;

	// World Config
	const int								WORLD_WIDTH	= 20;
	const int								WORLD_HEIGHT = 12;
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
		const std::array<sf::Vector2i, 5>	WAITING_CHAIR_POSITIONS = 
		{
			sf::Vector2i(3, 6),
			sf::Vector2i(4, 7),
			sf::Vector2i(4, 8),
			sf::Vector2i(2, 7),
			sf::Vector2i(2, 8),

		};

		// The position they actually wait at
		const std::array<sf::Vector2i, 5>	WAITING_CHAIR_SEATS =
		{
			sf::Vector2i(3, 5),
			sf::Vector2i(5, 7),
			sf::Vector2i(5, 8),
			sf::Vector2i(1, 7),
			sf::Vector2i(1, 8),
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



#endif

