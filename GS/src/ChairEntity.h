#ifndef CHAIRENTITY_H
#define CHAIRENTITY_H

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Glob.h"
class World;
class Customer;

class ChairEntity :
	public Entity
{
public:
	typedef std::unique_ptr<ChairEntity> ChairPtr;

	ChairEntity(TilePosition location, World* wp);
	bool isOccupied();
	bool setOccupied(bool occupied, Customer* occupant = nullptr);
	Customer* getOccupant();

	void setChairLocation(TilePosition tileLocation);
	TilePosition getChairLocation();

private:
	Customer* mOccupant;
	bool mOccupied;
	TilePosition mSeatLocation;
	void updateCurrent(sf::Time dt);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
