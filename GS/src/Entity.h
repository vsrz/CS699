#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceIdentifiers.h"
#include "SceneNode.h"

class Entity
	: public SceneNode
{
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
	void accelerate(float, float);
	void accelerate(sf::Vector2f);	
private:
	sf::Sprite mSprite;

	virtual void updateCurrent(sf::Time dt);
	sf::Vector2f mVelocity;

};

#endif