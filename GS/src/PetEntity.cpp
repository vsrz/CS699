
#include "PetEntity.h"
#include "World.h"

PetEntity::PetEntity(const TextureManager& textures, World* world)
	: ActorEntity(world)
{
	initalize(textures);
}

void PetEntity::initalize(const TextureManager& textures)
{
	mSprite.setTextureRect(sf::IntRect(Config::Pet::SPRITE_ANIM_OFFSET, Config::Pet::SPRITE_ANIM_FRAME_SIZE));
	mSprite.setTexture(textures.get(Textures::Kitty));
	mSprite.setScale(mWorld->getWorldScale());
	setTilePosition(Config::Pet::SPAWN_POSITION);
	setSpeed(2.f);
	setDirection(Direction::South);

}



