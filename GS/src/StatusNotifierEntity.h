#ifndef STATUSNOTIFIERENTITY_H
#define STATUSNOTIFIERENTITY_H

#pragma once

#include "Entity.h"

class World;
class Customer;

class StatusNotifierEntity :
	public Entity
{
public:
	StatusNotifierEntity(const TextureManager& textures, World* world, Customer* customer);

private:
	enum Status
	{
		None,
		Cut,
		Wash,
		Walk,
		Color,
		Pay,
	} mFrame;
	Customer* mCustomer;
	World* mWorld;
	SpritePosition mOffset;

	void updateStatus();
	void updateFrame();
	void updatePosition();

	virtual void updateCurrent(sf::Time dt);
};

#endif