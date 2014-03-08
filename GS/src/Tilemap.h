/**
 * Tilemap.h
 * Holds metadata and permits access to a map of tiles.
 *
 **/

#ifndef TILEMAP_H
#define TILEMAP_H

#pragma once
#include <string>
#include <vector>
#include <array>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Tile.h"

class Tilemap
{
public:
	Tilemap(int worldTileWidth, int worldTileHeight,
	float tileWidth, float tileHeight, float worldScale);

	/* Tile property checkers */
	bool isTileOccupied(int x, int y);
	bool isTileOccupied(sf::Vector2i screenPosition);
	bool isTileOccupied(sf::Vector2f screenPosition);
	template<typename T>
	bool isWaitingChair(T screenPosition);

	void setTileProperty(int x, int y, unsigned int tileProperty);
	unsigned int getTileProperty(sf::Vector2i screenPosition);
	unsigned int getTileProperty(int x, int y);
	sf::Vector2f getTilePixelPosition(int x, int y);
	
	Tile* getTile(int x, int y);
private:
	int toTileNumber(sf::Vector2i screenPosition);
	int toTileNumber(sf::Vector2f screenPosition);
	int toTileNumber(int x, int y);

	int mWorldWidth;
	int mWorldHeight;
	int mWorldScale;

	int mTileHeight;
	int mTileWidth;

	std::array<Tile,240> mTiles;
	
};

#endif
