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

	enum Type
	{
		Waiting,
		Washing,
		All,
	};

	ChairEntity(TilePosition location, World* wp);
	bool isOccupied();
	void setOccupied(Customer* occupant = nullptr);
	Customer* getOccupant();
	Type getChairType();
	void setChairType(Type type);

	void setChairLocation(TilePosition tileLocation);
	TilePosition getChairLocation();

private:
	Customer* mOccupant;
	TilePosition mStagingPosition;
	TilePosition mSeatingPosition;
	Direction mFacing;

	Type mType;
	void updateCurrent(sf::Time dt);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
