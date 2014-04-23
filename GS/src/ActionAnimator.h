#ifndef ACTIONANIMATOR_H
#define ACTIONANIMATOR_H

#pragma once
#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include "Animation.h"

class World;
class Player;

class ActionAnimator :
	public Entity
{
public:
	ActionAnimator(const TextureManager& textures, World* world, unsigned int type, Player* player);
	
	enum Type
	{
		None,
		Wash,
		Cut,
		Color,
	};

	enum State
	{
		Idle,
		Playing,

	};

	void setAnimationLocation(TilePosition tilePosition);
	void setTriggerTile(TilePosition tilePosition);
private:
	void initalize(const TextureManager& t, unsigned int type);
	virtual void updateCurrent(sf::Time dt);

	
	TilePosition mLocation;
	TilePosition mTriggerLocation;
	Animation mAnimation;
	unsigned short mState;
	unsigned short mType;

	Player* mPlayer;
};

#endif
