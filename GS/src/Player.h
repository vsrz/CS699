#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SFML/Window.hpp>
#include <map>
#include <iostream>
#include "ResourceIdentifiers.h"
#include "Entity.h"
#include "Actor.h"

class Player
	: public Entity
	, public Actor
{
public:
	enum Type
	{
		TestGuyWalking,
		Count,
	};
	Player(const TextureManager& textures, World* worldContext);
private:
	virtual void updateCurrent(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
	sf::Sprite mSprite;

	unsigned int getCategory() const;
};

#endif
