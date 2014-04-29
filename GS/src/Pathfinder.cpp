#include "Pathfinder.h"

Pathfinder::Pathfinder(Tilemap* tilemap)
	: mTilemap(tilemap)
{
	init();
}

void Pathfinder::init()
{
	mInitializedStartGoal = false;
	mFoundGoal = false;
	
}
void Pathfinder::clearOpenList()
{
	mOpenList.clear();
}

void Pathfinder::clearVisitedList()
{
	mVisitedList.clear();
}

void Pathfinder::clearPath()
{
	mPath.clear();
}

// Finds a valid destination. If the user clicks an "Occupied Tile" it will
// find the nest best tile to travel to
TilePosition Pathfinder::findValidDestination(TilePosition destination)
{
	int offset = 0;

	// If the destination tile chosen is valid, return the original destination
	if (mTilemap->getTile(
			static_cast<int>(destination.x)
		,	static_cast<int>(destination.y)) && 
		!mTilemap->isTileOccupied(
			static_cast<int>(destination.x)
		,	static_cast<int>(destination.y)))
		return destination;

	// Start from the original tile and go in a circle outward until
	// you find the first available valid tile to travel to
	sf::Vector2i dst(static_cast<int>(destination.x), static_cast<int>(destination.y));
	while (1)
	{
		// First try the tiles that are directly adjacent, without diagonals
		if (dst.y + 1 + offset <= Config::WORLD_HEIGHT - 1 &&
			!mTilemap->isTileOccupied(dst.x, dst.y + 1 + offset))
			return TilePosition(destination.x, destination.y + 1 + offset);

		if (dst.x - 1 - offset >= 0 &&
			!mTilemap->isTileOccupied(dst.x + -1 - offset, dst.y))
			return TilePosition(destination.x - 1 - offset, destination.y);

		if (dst.x + 1 <= Config::WORLD_WIDTH - 1 &&
			!mTilemap->isTileOccupied(dst.x + 1 + offset, dst.y))
			return TilePosition(destination.x + 1 + offset, destination.y);

		if (dst.y - 1 - offset >= 0 &&
			!mTilemap->isTileOccupied(dst.x, dst.y - 1 - offset))
			return TilePosition(destination.x, destination.y - 1 - offset);

		// Now, try the tile diagonally in a circle
		if (dst.x + 1 + offset <= Config::WORLD_WIDTH - 1 && 
			dst.y + 1 + offset <= Config::WORLD_HEIGHT - 1 &&
			!mTilemap->isTileOccupied(dst.x + 1 + offset, dst.y + 1 + offset))
			return TilePosition(destination.x + 1 + offset, destination.y + 1 + offset);

		if (dst.x - 1 - offset >= 0 &&
			dst.y + 1 + offset <= Config::WORLD_HEIGHT - 1 &&
			!mTilemap->isTileOccupied(dst.x - 1 - offset, dst.y + 1 + offset))
			return TilePosition(destination.x - 1 - offset, destination.y + 1 + offset);

		if (dst.x + 1 + offset <= Config::WORLD_WIDTH - 1 &&
			dst.y - 1 - offset >= 0 &&
			!mTilemap->isTileOccupied(dst.x + 1 + offset, dst.y - 1 - offset))
			return TilePosition(destination.x + 1 + offset, destination.y - 1 - offset);

		if (dst.x - 1 - offset >= 0 &&
			dst.y - 1 - offset >= 0 &&
			!mTilemap->isTileOccupied(dst.x - 1 - offset, dst.y - 1 - offset))
			return TilePosition(destination.x - 1 - offset, destination.y - 1 - offset);

		offset++;
	}
}


void Pathfinder::findPath(TilePosition currentPosition, TilePosition destPosition)
{
	// Maximum amount of tilesearches before pathfinding gives up
	int finder = 0;
	if (!mInitializedStartGoal)
	{
		for (auto& it : mOpenList)
			delete it;
		mOpenList.clear();

		for (auto& it : mVisitedList)
			delete it;
		mVisitedList.clear();

		mPath.clear();

		// Initialize the start and goal nodes
		PathNode start, goal;
		start.setCoordinates(currentPosition);

		// Find the goal
		goal.setCoordinates(findValidDestination(destPosition));

		setStartAndGoal(start, goal);
		mInitializedStartGoal = true;
	}
	
	// Once the start and goal have been initialized, begin the pathfinding
	while (!mFoundGoal && finder < Config::MAX_SEARCH)
	{
		if (mInitializedStartGoal)
		{
			finder++;
			continuePath();
		}
	}
}

std::vector<TilePosition> Pathfinder::getPath()
{
	return mPath;
}

void Pathfinder::setStartAndGoal(PathNode start, PathNode goal)
{
	mStartNode = new PathNode(start.getCoordinates(), nullptr);
	mGoalNode = new PathNode(goal.getCoordinates(), &goal);

	// Set the cost and the heuristic for the start node
	mStartNode->setCost(0);
	mStartNode->setHeuristic(mGoalNode);
	mStartNode->setParent(nullptr);

	// Add the start node to the OpenList
	mOpenList.push_back(mStartNode);

}

// Fetch the next node to test from the open list
PathNode* Pathfinder::getNextNode()
{
	int lowestCost = 32000;
	int nodeIndex = -1;
	PathNode* nextNode = nullptr;

	// Look through the openlist and get the node with the lowest total cost
	unsigned int size = mOpenList.size();
	for (int i = 0; i < size; i++)
	{
		if (mOpenList[i]->getScore() < lowestCost)
		{
			lowestCost = mOpenList[i]->getScore();
			nodeIndex = i;
		}
	}

	
	// The node we've found will be added to the visited list and removed from the open list
	if (nodeIndex >= 0)
	{
		nextNode = mOpenList[nodeIndex];
		mVisitedList.push_back(nextNode);
		mOpenList.erase(mOpenList.begin() + nodeIndex);
	}
	else
	{
		throw std::runtime_error("Could not find a valid path");
	}

	return nextNode;

}

void Pathfinder::pathOpened(int x, int y, int cost, PathNode* parent)
{
	//std::cout << std::endl << "Checking: " << x << "," << y << ")";
	// Do not pathfind nodes not in the tilemap
	if (!mTilemap->getTile(x,y))
	{
		return;
	}
	// Check if this space is occupied
	if (mTilemap->isTileOccupied(x, y))
	{
		return;
	}

	// Do not visit any nodes already visited
	TilePosition coordinate(static_cast<float>(x), static_cast<float>(y));
	size_t size = mVisitedList.size();
	for (int i = 0; i < size; i++)
	{
		if (coordinate == mVisitedList[i]->getCoordinates())
			return;
	}

	PathNode* newChild = new PathNode(x, y, parent);
	newChild->setCost(cost);
	newChild->setHeuristic(mGoalNode);
	//std::cout << "New child";
	// With the new child, check to see if there was a better
	// way to get to this node that had been found previously
	size = mOpenList.size();
	for (int i = 0; i < mOpenList.size(); i++)
	{
		if (coordinate == mOpenList[i]->getCoordinates())
		{
			int newCost = newChild->getScore() + cost + mOpenList[i]->getScore();
			if (mOpenList[i]->getScore() > newCost)
			{
				mOpenList[i]->setCost(newChild->getScore() + cost);
				mOpenList[i]->setParent(newChild);
			}
			
			// If this isn't better than the one in the list, get rid of the new child
			else
			{
				delete newChild;
				return;

			}
		}
	}
	mOpenList.push_back(newChild);


}

void Pathfinder::continuePath()
{
	// If there are no unvisited nodes, return
	if (mOpenList.empty())
	{
		return;
	}

	PathNode* currentNode = getNextNode();

	// If we have reached the goal, then set the parent to the current cell
	if (currentNode->getCoordinates() == mGoalNode->getCoordinates())
	{
		mGoalNode->setParent(currentNode->getParent());
		PathNode* getPath;
		
		// Recursively build the calculated path to the start from the goal
		for (getPath = mGoalNode; getPath != nullptr; getPath = getPath->getParent())
		{
			mPath.push_back(getPath->getCoordinates());
		}

		mFoundGoal = true;
		return;
	}

	// If we haven't reached the goal, try adjacent squares
	else
	{
		// Right square
		pathOpened(
				static_cast<int>(currentNode->getCoordinates().x) + 1
			,	static_cast<int>(currentNode->getCoordinates().y)
			,   currentNode->getCost() + 10, currentNode);

		// Left square
		pathOpened(currentNode->getCoordinates().x - 1, currentNode->getCoordinates().y, 
			currentNode->getCost() + 10, currentNode);

		// Top square
		pathOpened(currentNode->getCoordinates().x, currentNode->getCoordinates().y - 1, 
			currentNode->getCost() + 10, currentNode);

		// Bottom square
		pathOpened(currentNode->getCoordinates().x, currentNode->getCoordinates().y + 1, 
			currentNode->getCost() + 10, currentNode);

		// Up-right square
		pathOpened(currentNode->getCoordinates().x + 1, currentNode->getCoordinates().y - 1, 
			currentNode->getCost() + 14, currentNode);

		// Up-Left square
		pathOpened(currentNode->getCoordinates().x - 1, currentNode->getCoordinates().y - 1, 
			currentNode->getCost() + 14, currentNode);

		// Bottom-left square
		pathOpened(currentNode->getCoordinates().x - 1, currentNode->getCoordinates().y + 1, 
			currentNode->getCost() + 14, currentNode);

		// Bottom-right square
		pathOpened(currentNode->getCoordinates().x + 1, currentNode->getCoordinates().y + 1, 
			currentNode->getCost() + 14, currentNode);
		
		// Find the current node and remove it from the OpenList
		for (int i = 0; i < mOpenList.size(); i++)
		{
			if (currentNode->getCoordinates() == mOpenList[i]->getCoordinates())
			{
				mOpenList.erase(mOpenList.begin() + i);
			}
		}
	}

}

TilePosition Pathfinder::nextPathPos()
{
	// get the first position from the shortest path on the list
	int index = 1;

	TilePosition nextNode;
	nextNode.x = mPath[mPath.size() - index].x;
	nextNode.y = mPath[mPath.size() - index].y;

//	sf::Vector2i distance = nextNode - pos;

	if (index < mPath.size())
	{
		//if (distance.Length() < radius)
		//{
		//	mPath.erase(mPath.end() - index);
		//}
	}

	return nextNode;

}
