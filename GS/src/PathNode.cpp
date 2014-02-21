#include "PathNode.h"


PathNode::PathNode(void)
	: mParent(nullptr)
	, mClosed(false)
	, mOpened(false)
	, mHeuristic(999)
	, mCost(999)
	, mTile()
{

}

// mCost is G Score (cost to get to this node)
// mHeuristic is H Score (estimateds score to get to goal)
// F is the estimated score using this path to get to the goal

void PathNode::setOpen(bool open)
{
	mOpened = open;
}

void PathNode::setClose(bool close)
{
	mClosed = close;
}

sf::Vector2i PathNode::getTileLocation()
{
	return mTileLocation;
}
int PathNode::getHeuristic(PathNode* node)
{
	return node->mHeuristic	+ 
		(abs(mTileLocation.x == node->getTileLocation().x) ||
		 abs(mTileLocation.y == node->getTileLocation().y) ? 10 : 14);

}

int PathNode::getAccumulatedCost(PathNode* node)
{
	
}

int PathNode::getHeuristic()
{
	return mHeuristic;
}

int PathNode::getAccumulatedCost()
{
	return mCost;
}


