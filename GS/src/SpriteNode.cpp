#include "SpriteNode.h"

SpriteNode::SpriteNode()
	: mEmpty(true)
{
	
}

SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
	, mEmpty(false)
{

}

SpriteNode::SpriteNode(sf::Sprite sprite)
	: mSprite(sprite)
	, mEmpty(false){

}
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
	: mSprite(texture, rect)
	, mEmpty(false)
{
}

bool SpriteNode::isEmpty()
{
	return mEmpty;
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

