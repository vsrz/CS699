#include "World.h"
#include "CashRegister.h"


CashRegister::CashRegister()
{

}

std::vector<TilePosition> CashRegister::getTilePositions()
{
	std::vector<TilePosition> pos;
	pos.push_back(Config::RegisterQueue::REGISTER_POSITION[0]);
	pos.push_back(Config::RegisterQueue::REGISTER_POSITION[1]);
	return pos;
}

