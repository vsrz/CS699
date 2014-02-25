
#ifndef PATHFINDER_H
#define PATHFINDER_H

#pragma once

#include <SFML/System.hpp>
#include <vector>
#include <array>
#include <string>
#include <memory>
#include <algorithm>
#include "Tilemap.h"
#include "PathNode.h"

class Pathfinder
{
public:
	Pathfinder(Tilemap* tilemap);
	
	void findPath(sf::Vector2i currentPosition, sf::Vector2i destPosition);
	sf::Vector2i  nextPath();

	void clearOpenList();
	void clearVisitedList();
	void clearPath();


private:
	Tilemap* mTilemap;
	bool mInitializedStartGoal;
	bool mFoundGoal;
	std::vector<PathNode*> mOpenList, mVisitedList;
	std::vector<sf::Vector2i> mPath;
	PathNode *mStartNode, *mGoalNode;
	sf::Vector2i nextPathPos();

	void setStartAndGoal(PathNode start, PathNode goal);
	void pathOpened(int x, int y, int cost, PathNode* parent);

	PathNode *getNextNode();
	void continuePath();
	
};

#endif
