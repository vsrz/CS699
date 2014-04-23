#ifndef HEARTENTITY_H
#define HEARTENTITY_H

#pragma once

#include "Entity.h"

class World;

class HeartEntity :
	public Entity
{
public:
	HeartEntity(const TextureManager& textures, World* world);
};

#endif
