#include "PathNode.h"


PathNode::PathNode(void)
	: mParent(nullptr)
	, mClosed(false)
	, mOpened(false)
	, mHeuristic(999)
	, mCost(999)
{

}

PathNode::PathNode(int x, int y, PathNode* parent)
	: mParent(parent)
	, mCoordinates(sf::Vector2i(x, y))
{

}

PathNode::PathNode(sf::Vector2i coordinate, PathNode* parent)
	: mParent(parent)
	, mCoordinates(coordinate)
{

}


// mCost is G Score (cost to get to this node)
// mHeuristic is H Score (estimateds score to get to goal)
// F is the estimated score using this path to get to the goal

void PathNode::setHeuristic(PathNode* end)
{
	mHeuristic = abs(mCoordinates.x - end->getCoordinates().x) +
		abs(mCoordinates.y - end->getCoordinates().y);
}

PathNode* PathNode::getParent()
{
	return mParent;
}

void PathNode::setCost(int g)
{
	mCost = g;
}

int PathNode::getCost()
{
	return mCost;
}

void PathNode::setParent(PathNode* parent)
{
	mParent = parent;
}

void PathNode::setCoordinates(sf::Vector2i coordinate)
{
	mCoordinates = coordinate;
}

sf::Vector2i PathNode::getCoordinates()
{
	return mCoordinates;
}

int PathNode::getScore()
{
	return mHeuristic + mCost;
}

int PathNode::getHeuristic()
{
	return mHeuristic;
}