#ifndef CUSTOMER_H
#define CUSTOMER_H

#pragma once
#include "ActorEntity.h"

class World;

class Customer :
	public ActorEntity
{
public:
	Customer(const TextureManager& textures, World* world);
	~Customer(void);
	virtual void updateCurrent(sf::Time dt);

};

#endif
