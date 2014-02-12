#ifndef Actor
#define Actor_H

#pragma once

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

namespace Direction
{
	enum Type
	{
		None	= 0,
		North	= 1 << 0,
		East	= 1 << 1,
		South	= 1 << 2,
		West	= 1 << 3,
	};
}

class Actor
{
public:
	enum Type
 	{
		Player,
		Customer1,
		Customer2,
	};

	Actor();
	void setDestination(sf::Vector2i destination);

private:
	void findDestination();
	bool hasReachedDestination();
	void updateCurrent(sf::Time dt);

	Type mType;

	sf::Vector2i mTileDestination;
	sf::Vector2i mTilePosition;
};

#endif
