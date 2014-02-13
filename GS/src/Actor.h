#ifndef Actor
#define Actor_H

#pragma once

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

namespace Action
{
	enum Direction
	{
		None	= 0,
		South	= 1 << 1,
		North	= 1 << 2,
		West	= 1 << 3,
		East	= 1 << 4,
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
	bool hasReachedDestination();

	sf::Vector2i getDestination();
protected:
	void findDestination();
	virtual void updateCurrent(sf::Time dt);

	unsigned int mDirection;
	sf::Vector2i mTileDestination;
};

#endif
