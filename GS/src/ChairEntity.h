#ifndef CHAIRENTITY_H
#define CHAIRENTITY_H

#pragma once

#include <memory>
#include "Entity.h"
#include <SFML/System.hpp>

class World;

class ChairEntity :
	public Entity
{
public:
	typedef std::unique_ptr<ChairEntity> ChairPtr;

	ChairEntity(sf::Vector2i location, World* wp);
	bool isOccupied();
	bool setOccupied(bool occupied);
private:
	bool mOccupied;
	void updateCurrent(sf::Time dt);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
