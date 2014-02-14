#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SFML/Window.hpp>
#include <map>
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
	virtual void updateCurrent(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
	sf::Sprite mSprite;
	World* mWorld;
	bool hasReachedDestination();
	
	float mSpeed;
	sf::Vector2i mTilePosition;
	sf::Vector2i mTileDestination;
	sf::Vector2i mFrameSize;
	sf::Time movementUpdate;

	unsigned int getCategory() const;
};

#endif
