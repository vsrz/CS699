#ifndef PATHNODE_H
#define PATHNODE_H

#pragma once

#include <memory>
#include <list>
#include <cmath>
#include <SFML/System.hpp>
#include "Tile.h"
#include "Glob.h"
class PathNode
{
public:
	PathNode(void);
	PathNode(int x, int y, PathNode* parent);
	PathNode(TilePosition coordinate, PathNode* parent);


	int getScore();
	int getCost();
	int getHeuristic();
	TilePosition getCoordinates();
	PathNode* getParent();

	void setHeuristic(PathNode *end);
	void setCost(int g);
	void setParent(PathNode* parent);
	void setCoordinates(TilePosition coordinate);

private:
	PathNode *mParent;
	bool mClosed;
	bool mOpened;
	
	int mHeuristic;
	int mCost;

	TilePosition mCoordinates;

};

#endif
