#ifndef GLOB_H
#define GLOB_H

#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/* Dirty global configuration area, for now (forever?) */
namespace Config
{
	// Manager (PC) Config
	static float		MANAGER_SPEED = 0.5f;

	// World Config
	static int			WORLD_WIDTH	= 20;
	static int			WORLD_HEIGHT = 12;
	static float		WORLD_SCALE = 2.f;
	
	// Tiles
	const char*	const	TILEMAP_FILENAME = "res/Tilemap.tmx";		
	static float		TILE_WIDTH = 32.f;
	static float		TILE_HEIGHT = 32.f;

	// Pathfinder
	static int			MAX_SEARCH = 500;
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

