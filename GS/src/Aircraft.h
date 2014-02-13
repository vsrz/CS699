#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "ResourceIdentifiers.h"

class Aircraft :
	public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};

	Aircraft(Type type, const TextureManager& textures);
	unsigned int getCategory() const;
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	Type mType;
	sf::Sprite mSprite;
};

#endif
