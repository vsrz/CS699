
#ifndef PATHNODE_H
#define PATHNODE_H

#pragma once

#include <memory>
#include <list>
#include <SFML/System.hpp>
#include "Tile.h"

class PathNode
{
public:
	PathNode(void);
	PathNode(Tile* mTile);

	void setOpen(bool open = true);
	void setClose(bool close = true);
	int getHeuristic();
	int getAccumulatedCost();
	int getTotalCost();
	int getAccumulatedCost(PathNode* node);
	int getHeuristic(PathNode* node);
	sf::Vector2i getTileLocation();
private:
	std::unique_ptr<PathNode> mParent;
	bool mClosed;
	bool mOpened;
	
	Tile* mTile;
	int mHeuristic;
	int mCost;

	sf::Vector2i mTileLocation;

};

#endif
