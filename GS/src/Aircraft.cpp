#include "ResourceManager.h"
#include "Aircraft.h"


Textures::ID toTextureID(Aircraft::Type type)
{
	switch(type)
	{
	case Aircraft::Eagle:
		return Textures::Eagle;
	case Aircraft::Raptor:
		return Textures::Raptor;
	}
	return Textures::Eagle;
}

Aircraft::Aircraft(Type type, const TextureManager& textures) 
	: mType(type)
	, mSprite(textures.get(toTextureID(type)))
{
	// Align the origin for this object
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Eagle:
		return Category::PlayerAircraft;
	default:
		return Category::EnemyAircraft;
	}
}



