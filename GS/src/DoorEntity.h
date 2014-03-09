#ifndef DOORENTITY_H
#define DOORENTITY_H

#pragma once
#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "Animation.h"

class World;

class DoorEntity :
	public Entity
{
public:
	DoorEntity(const TextureManager& textures, World* world);

private:
	void initalize();
	void setTriggerTiles();
	enum State
	{
		None,
		Closed,
		Opening,
		Open,
		Closing,
	};

	Animation mAnimDoorOpen;
	Animation mAnimDoorClose;
	Animation* mActiveAnimation;
	sf::Time mElapsedTime;
	unsigned short mState;
	std::vector<sf::Vector2i> triggerTiles;

	bool checkDoorToggle();
	virtual void updateCurrent(sf::Time dt);
};

#endif
