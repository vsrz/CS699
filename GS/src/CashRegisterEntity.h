#ifndef CASHREGISTERENTITY_H
#define CASHREGISTERENTITY_H

#pragma once

#include "Glob.h"
#include "Entity.h"
#include "RegisterQueue.h"

class CashRegisterEntity :
	public Entity
{
public:
	CashRegisterEntity(const TextureManager& textures, World* world, RegisterQueue* queue);

private:
	virtual void updateCurrent(sf::Time dt);
	bool queueIsActive();
	RegisterQueue* mQueue;
	int mFlashDelay;
	sf::Time mTimer;
	bool mFullBrightness;
	bool mEnabled;
};

#endif