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
	, mCoordinates(TilePosition(static_cast<int>(x), static_cast<int>(y)))
{

}

PathNode::PathNode(TilePosition coordinate, PathNode* parent)
	: mParent(parent)
	, mCoordinates(coordinate)
{

}


// mCost is G Score (cost to get to this node)
// mHeuristic is H Score (estimateds score to get to goal)
// F is the estimated score using this path to get to the goal

void PathNode::setHeuristic(PathNode* end)
{
	mHeuristic = static_cast<int>(abs(mCoordinates.x - end->getCoordinates().x) +
		abs(mCoordinates.y - end->getCoordinates().y));
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

void PathNode::setCoordinates(TilePosition coordinate)
{
	mCoordinates = coordinate;
}

TilePosition PathNode::getCoordinates()
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
