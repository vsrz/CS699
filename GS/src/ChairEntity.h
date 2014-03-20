#ifndef CHAIRENTITY_H
#define CHAIRENTITY_H

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class World;
class Customer;

class ChairEntity :
	public Entity
{
public:
	typedef std::unique_ptr<ChairEntity> ChairPtr;

	ChairEntity(sf::Vector2i location, World* wp);
	bool isOccupied();
	bool setOccupied(bool occupied, Customer* occupant = nullptr);
	Customer* getOccupant();

	void setChairLocation(sf::Vector2i tileLocation);
	sf::Vector2i getChairLocation();

private:
	Customer* mOccupant;
	bool mOccupied;
	sf::Vector2i mSeatLocation;
	void updateCurrent(sf::Time dt);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
