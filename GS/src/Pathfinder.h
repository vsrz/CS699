#ifndef PATHFINDER_H
#define PATHFINDER_H

#pragma once

#include <SFML/System.hpp>
#include <vector>
#include <array>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include "Tilemap.h"
#include "PathNode.h"
#include "Glob.h"

class Pathfinder
{
public:
	Pathfinder(Tilemap* tilemap);
	
	TilePosition findValidDestination(TilePosition destination);
	void findPath(TilePosition currentPosition, TilePosition destPosition);
	TilePosition nextPath();


	void clearOpenList();
	void clearVisitedList();
	void clearPath();
	std::vector<TilePosition> getPath();


private:
	Tilemap* mTilemap;
	bool mInitializedStartGoal;
	bool mFoundGoal;
	std::vector<PathNode*> mOpenList, mVisitedList;
	std::vector<TilePosition> mPath;
	PathNode *mStartNode, *mGoalNode;
	TilePosition nextPathPos();

	void setStartAndGoal(PathNode start, PathNode goal);
	void pathOpened(int x, int y, int cost, PathNode* parent);

	PathNode *getNextNode();
	void continuePath();
	void init();
	
};

#endif
