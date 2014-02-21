#include "Pathfinder.h"


Pathfinder::Pathfinder(Tilemap* tilemap)
	: mTilemap(tilemap)
{
}

std::vector<sf::Vector2i> Pathfinder::findPath(int cx, int cy, int dx, int dy)
{
	std::vector<sf::Vector2i> path;

	// Define the starting points
	PathNodePtr start = PathNodePtr(new PathNode(mTilemap->getTile(cx, cy)));
	PathNodePtr end = PathNodePtr(new PathNode(mTilemap->getTile(dx, dy)));
	PathNodePtr current;
	PathNodePtr child;

	// Define the open and closed list for this path
	PathNodeList openList;
	PathNodeList closedList;

	// Push the current node into the opened tile list
	openList.push_back(start);
	start->setOpen();

	unsigned int n = 0;

	while (n == 0 || (current != end && n < 50))
	{
        // Look for the smallest F value in the openList and make it the current point
		for (PathNodeList::iterator i = openList.begin(); i != openList.end(); ++i)
		{
			if (i == openList.begin() || (*i)->getCost() <= current->getCost())
			{
				current = PathNodePtr((*i).get());
			}
			
			if (current == end) 
			{
				break;
			}
		}

		// Remove the current point from the list
		openList.remove(current);
		current->setOpen(false);

		// Add current point to the closedList
		closedList.push_back(current);
		current->setClose();

		// Get all of the current node's adjacent walkable tiles
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}

				// This point
				
			}
		}

	}




	return path;
}

