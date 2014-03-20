#include "Customer.h"
#include "ChairEntity.h"
#include "World.h"


ChairEntity::ChairEntity(sf::Vector2i tilePosition, World* wp)
	: Entity(wp)
{
	mOccupied = false;
	wp->mTilemap.setTileProperty(tilePosition.x, tilePosition.y, Tiles::Property::WaitingChair);
	mPosition = toSpritePosition(tilePosition);
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

void ChairEntity::setChairLocation(sf::Vector2i tileLocation)
{
	mSeatLocation = tileLocation;
}

sf::Vector2i ChairEntity::getChairLocation()
{
	return mSeatLocation;
}

void ChairEntity::updateCurrent(sf::Time dt)
{

}

void ChairEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}