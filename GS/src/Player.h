#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SFML/Window.hpp>
#include <map>
#include <math.h>
#include <iostream>
#include "ResourceIdentifiers.h"
#include "Entity.h"
#include "Actor.h"
#include "World.h"
class World;

class Player
	: public SceneNode
{
public:
	enum Type
	{
		TestGuyWalking,
		Count,
	};

	Player(const TextureManager& textures, World* worldContext);
	void setDestination(sf::Vector2i destination);

private:
	enum Direction
	{
		None = 0,
		South = 1 << 1,
		North = 1 << 2,
		West = 1 << 3,
		East = 1 << 4,
	};

	virtual void updateCurrent(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
	sf::Sprite mSprite;
	World* mWorld;
	bool hasReachedDestination();
	float mSpeed;
	sf::Vector2i mTilePosition;
	sf::Vector2i mTileDestination;
	sf::Vector2i mSpawnPosition;
	
	// Animation related 
	void advanceFrame();
	void checkDirection();
	sf::Vector2i mFrameSize;
	std::size_t mFrame;
	std::size_t mNumFrames;
	std::size_t mFrameOffset;
	sf::Vector2f mScale;
	sf::Time mElapsedTime;

	unsigned int mDirection;
	unsigned int getCategory() const;
};

#endif
