
#ifndef PATHNODE_H
#define PATHNODE_H

#pragma once

#include <memory>
#include <list>
#include <cmath>
#include <SFML/System.hpp>
#include "Tile.h"

class PathNode
{
public:
	PathNode(void);
	PathNode(int x, int y, PathNode* parent);
	PathNode(sf::Vector2i coordinate, PathNode* parent);


	int getScore();
	int getCost();
	int getHeuristic();
	sf::Vector2i getCoordinates();
	PathNode* getParent();

	void setHeuristic(PathNode *end);
	void setCost(int g);
	void setParent(PathNode* parent);
	void setCoordinates(sf::Vector2i coordinate);

private:
	PathNode *mParent;
	bool mClosed;
	bool mOpened;
	
	int mHeuristic;
	int mCost;

	sf::Vector2i mCoordinates;

};

#endif
