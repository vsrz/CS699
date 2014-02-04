#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#pragma once
#include "Entity.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>

class Aircraft :
	public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};

	Aircraft(Type type, const TextureHolder& textures);
	unsigned int getCategory() const;
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	Type mType;
	sf::Sprite mSprite;
};

#endif
