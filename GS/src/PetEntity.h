#ifndef PETENTITY_H
#define PETENTITY_H

#pragma once

#include "ActorEntity.h"

class World;

class PetEntity :
	public ActorEntity
{
public:
	PetEntity(const TextureManager& textures, World* world);

private:
	void initalize(const TextureManager& t);
};

#endif
