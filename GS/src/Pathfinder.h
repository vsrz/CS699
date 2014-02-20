
#ifndef PATHFINDER_H
#define PATHFINDER_H

#pragma once

#include <SFML/System.hpp>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include "Tilemap.h"

class Pathfinder
{
public:
	Pathfinder(Tilemap* tilemap);
	std::vector<sf::Vector2i> findPath(int x, int y, int dx, int dy);
private:
	Tilemap* mTilemap;
	
};

#endif