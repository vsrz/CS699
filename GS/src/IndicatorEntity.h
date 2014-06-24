#ifndef INDICATORENTITY_H
#define INDICATORENTITY_H

#pragma once

#include "Glob.h"
#include "Entity.h"
#include "ChairEntity.h"

class IndicatorEntity :
	public Entity
{
public:
	IndicatorEntity(const TextureManager& textures, World* world, ChairEntity* chair);
	void activiate();
	void setDuration(sf::Time seconds);
private:
	// The direction the arrow is traveling
	bool mGoingDown;

	// The remaining time to display the arrow
	sf::Time mTimer;

	// The duration that the arrow will run when activated
	sf::Time mDuration;

	// Arrow positions
	SpritePosition mStartPosition;
	SpritePosition mEndPosition;
	SpritePosition mPosition;

	// Arrow positions
	
	// The position of the chair that the indicator is attached to
	ChairEntity* mChairPosition;
	
	// The maximum height of the bounce of the arrow
	float mMaxHeight;
	
	virtual void updateCurrent(sf::Time dt);
};

#endif