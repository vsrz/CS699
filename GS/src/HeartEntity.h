#ifndef HEARTENTITY_H
#define HEARTENTITY_H

#pragma once

#include "Entity.h"

class World;
class Customer;


class HeartEntity :
	public Entity
{
public:
	HeartEntity(const TextureManager& textures, World* world, float love, Customer* customer);

	void setMaxFill(float fill);
	void setFill(float fill);
private:
	float mLove;
	float mLoveMax;
	int mFrame;
	
	void updateCurrent(sf::Time dt);
	void updateStatusPosition();
	void updateFrame();
	void setFrame(int frame);
	Customer *mCustomer;
};

#endif
