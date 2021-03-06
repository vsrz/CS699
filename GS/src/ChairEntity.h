#ifndef CHAIRENTITY_H
#define CHAIRENTITY_H

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Glob.h"
class World;
class Customer;
class IndicatorEntity;

class ChairEntity :
	public Entity
{
public:
	typedef std::unique_ptr<ChairEntity> ChairPtr;

	enum Type
	{
		Waiting,
		Washing,
		Cutting,
		Coloring,
		All,
	};

	ChairEntity(TilePosition location, World* wp);
	bool isOccupied();
	void setOccupied(Customer* occupant = nullptr);
	Customer* getOccupant();
	Type getChairType();
	void setChairType(Type type);

	void setChairPosition(TilePosition tilePosition);
	void setStagingPosition(TilePosition tilePosition);
	void setOperatingPosition(TilePosition tilePosition);
	void setDirection(Direction direction);
	void setHelper(IndicatorEntity* indicator);
	void activateHelper();

	TilePosition convertAltClickPosition(TilePosition pos);
	TilePosition getChairPosition();
	TilePosition getStagingPosition();
	TilePosition getOperatingPosition();
	Direction getDirection();

private:
	Customer* mOccupant;
	TilePosition mStagingPosition;
	TilePosition mSeatingPosition;
	TilePosition mOperatingPosition;
	Direction mDirection;

	// Up to two indicator arrow helpers for each chair type
	std::array<IndicatorEntity*, 2u> mIndicatorArrows;

	Type mType;
	void updateCurrent(sf::Time dt);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
