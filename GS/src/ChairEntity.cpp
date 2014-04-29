#include "Customer.h"
#include "ChairEntity.h"
#include "World.h"


ChairEntity::ChairEntity(TilePosition tilePosition, World* wp)
	: Entity(wp)
{
	wp->mTilemap.setTileProperty(
			static_cast<int>(tilePosition.x)
		,	static_cast<int>(tilePosition.y)
		,	Tiles::Property::WaitingChair);
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

void ChairEntity::setChairPosition(TilePosition tilePosition)
{
	mSeatingPosition = tilePosition;
}

void ChairEntity::setDirection(Direction direction)
{
	mDirection = direction;
}

Direction ChairEntity::getDirection()
{
	return mDirection;
}

// This is the actual seating position of the chair
TilePosition ChairEntity::getChairPosition()
{
	return mSeatingPosition;
}

// This is the position that the customer will stand in before getting into the chair
TilePosition ChairEntity::getStagingPosition()
{
	return mStagingPosition;
}

// This is the position that the manager should be in when performing a service
// for this chair
TilePosition ChairEntity::getOperatingPosition()
{
	return mOperatingPosition;
}

void ChairEntity::setStagingPosition(TilePosition tilePosition)
{
	mStagingPosition = tilePosition;
}

void ChairEntity::setOperatingPosition(TilePosition tilePosition)
{
	mOperatingPosition = tilePosition;
}

void ChairEntity::updateCurrent(sf::Time dt)
{

}

void ChairEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}