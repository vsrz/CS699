#include "Customer.h"
#include "ChairEntity.h"
#include "World.h"


ChairEntity::ChairEntity(TilePosition tilePosition, World* wp)
	: Entity(wp)
{
	mOccupied = false;
	wp->mTilemap.setTileProperty(tilePosition.x, tilePosition.y, Tiles::Property::WaitingChair);
	setTilePosition(tilePosition);
	mType = Type::Waiting;
}

bool ChairEntity::isOccupied()
{
	return mOccupied;
}

Customer* ChairEntity::getOccupant()
{
	return mOccupant;
}

// returns true if the operation was a success
bool ChairEntity::setOccupied(bool occupied, Customer* occupant)
{
	if (mOccupied == occupied)
	{
		mOccupant = nullptr;
		return false;
	}
	mOccupant = occupant;
	mOccupied = occupied;
	return true;
}

ChairEntity::Type ChairEntity::getChairType()
{
	return mType;
}

void ChairEntity::setChairType(Type type)
{
	mType = Waiting;
	if (type < All)
	{
		mType = type;
	}
}

void ChairEntity::setChairLocation(TilePosition tileLocation)
{
	mSeatingPosition = tileLocation;
}

TilePosition ChairEntity::getChairLocation()
{
	return mSeatingPosition;
}

void ChairEntity::updateCurrent(sf::Time dt)
{

}

void ChairEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}