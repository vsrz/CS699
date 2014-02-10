#ifndef NPCENTITY_H
#define NPCENTITY_H

#pragma once

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

class NpcEntity
	: public Entity
{
public:
	enum Type
 	{
		TestGuy,
	};

	NpcEntity(Type type, const TextureManager& textures);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
	Type mType;
	sf::Sprite mSprite;
};

#endif
