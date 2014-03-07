#include "ChairEntity.h"
#include "Tile.h"
#include "World.h"

ChairEntity::ChairEntity(sf::Vector2i tilePosition, World* wp)
	: Entity(wp)

{
	setPosition(tilePosition);
	mOccupied = false;
	wp->mTilemap.setTileProperty(tilePosition.x, tilePosition.y, Tiles::Property::WaitingChair);
}

bool ChairEntity::isOccupied()
{
	return mOccupied;
}

// returns true if the operation was a success
bool ChairEntity::setOccupied(bool occupied)
{
	if (mOccupied == occupied)
		return false;
	mOccupied = occupied;
	return true;
}

void ChairEntity::updateCurrent(sf::Time dt)
{

}

void ChairEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}