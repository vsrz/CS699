#include "Aircraft.h"
#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>


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

Aircraft::Aircraft(Type type, const TextureHolder& textures) 
	: mType(type)
	, mSprite(textures.get(toTextureID(type)))
{
	if (type == Textures::Eagle)
	{
		mSprite.setScale(0.2f, 0.2f);
	}
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



