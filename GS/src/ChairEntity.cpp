#include "Customer.h"
#include "ChairEntity.h"
#include "World.h"


ChairEntity::ChairEntity(TilePosition tilePosition, World* wp)
	: Entity(wp)
{
	wp->mTilemap.setTileProperty(tilePosition.x, tilePosition.y, Tiles::Property::WaitingChair);
	setTilePosition(tilePosition);
	mType = Type::Waiting;
	mOccupant = nullptr;
}

bool ChairEntity::isOccupied()
{
	return mOccupant != nullptr;
}

Customer* ChairEntity::getOccupant()
{
	return mOccupant;
}

// returns true if the operation was a success
void ChairEntity::setOccupied(Customer* occupant)
{
	mOccupant = occupant;
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