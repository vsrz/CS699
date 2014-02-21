
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
	std::vector<sf::Vector2i> findPath(int x, int y, int dx, int dy);
	typedef std::unique_ptr<PathNode> PathNodePtr;
	typedef std::list<PathNodePtr> PathNodeList;

private:
	Tilemap* mTilemap;
	
};

#endif
