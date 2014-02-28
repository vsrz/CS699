
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

// Maximum amount of squares it will search during pathfinding
// before giving up
#define MAX_SEARCH 500

class Pathfinder
{
public:
	Pathfinder(Tilemap* tilemap);
	
	sf::Vector2i findValidDestination(sf::Vector2i destination);
	void findPath(sf::Vector2i currentPosition, sf::Vector2i destPosition);
	sf::Vector2i nextPath();


	void clearOpenList();
	void clearVisitedList();
	void clearPath();
	std::vector<sf::Vector2i> getPath();


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
	void init();
	
};

#endif
