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

void Pathfinder::findPath(sf::Vector2i currentPosition, sf::Vector2i destPosition)
{
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
		goal.setCoordinates(destPosition);

		setStartAndGoal(start, goal);
		mInitializedStartGoal = true;
	}
	
	// Once the start and goal have been initialized, begin the pathfinding
	while (!mFoundGoal)
	{
		if (mInitializedStartGoal)
		{
			continuePath();
		}
	}

	std::cout << std::endl << "From: (" << currentPosition.x << "," << currentPosition.y << ") To: (";
	std::cout << destPosition.x << "," << destPosition.y << ")" << std::endl;
	for (auto& i : mPath)
	{
		std::cout << "(" << i.x << "," << i.y << ") ";
	}
	std::cout << std::endl;

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
	int lowestCost = 250;
	int nodeIndex = -1;
	PathNode* nextNode = nullptr;

	// Look through the openlist and get the node with the lowest total cost
	for (int i = 0; i < mOpenList.size(); i++)
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

	return nextNode;

}

void Pathfinder::pathOpened(int x, int y, int cost, PathNode* parent)
{
	// Check if this space is occupied
	if (mTilemap->isTileOccupied(x, y))
	{
		//return;
		std::cout << "Occupied!" << std::endl;
	}

	// Do not visit any nodes already visited
	sf::Vector2i coordinate(x, y);
	for (int i = 0; i < mVisitedList.size(); i++)
	{
		if (coordinate == mVisitedList[i]->getCoordinates())
			return;
	}

	PathNode* newChild = new PathNode(x, y, parent);
	newChild->setCost(cost);
	newChild->setHeuristic(mGoalNode);

	// With the new child, check to see if there was a better
	// way to get to this node that had been found previously
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
		pathOpened(currentNode->getCoordinates().x + 1, currentNode->getCoordinates().y, 
			currentNode->getCost() + 10, currentNode);

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

sf::Vector2i Pathfinder::nextPathPos()
{
	// get the first position from the shortest path on the list
	int index = 1;

	sf::Vector2i nextNode;
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