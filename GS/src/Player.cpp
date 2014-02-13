#include "ResourceManager.h"
#include "Player.h"
#include <iostream>

Player::Player(const TextureManager& textures) 
	: mSprite(textures.get(Textures::TestGuy))
{

}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);

}

/**
 * Need to explicitly call all updates for this object
 **/
void Player::updateCurrent(sf::Time dt)
{
	Actor::updateCurrent(dt);
	Entity::updateCurrent(dt);
}

unsigned int Player::getCategory() const 
{ 
	return Category::Player; 
}


