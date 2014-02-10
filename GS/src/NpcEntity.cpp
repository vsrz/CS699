#include "NpcEntity.h"


Textures::ID toTextureID(NpcEntity::Type type)
{
	switch(type)
	{
	case NpcEntity::TestGuy:
		return Textures::TestGuy;
	}
	return Textures::TestGuy;
}

NpcEntity::NpcEntity(Type type, const TextureManager& textures)
	: mType(type)
	, mSprite(textures.get(toTextureID(type)))
{
	mSprite.setTextureRect(sf::IntRect(0, 0, 32, 64));

}

void NpcEntity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}