#include "SpriteNode.h"

SpriteNode::SpriteNode()
	: mNoTexture(false)
{
	
}

SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
	, mNoTexture(false)
{

}

SpriteNode::SpriteNode(sf::Sprite sprite)
	: mSprite(sprite)
	, mNoTexture(false)
{
}
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
	: mSprite(texture, rect)
	, mNoTexture(false)
{
}
SpriteNode::SpriteNode(const sf::RectangleShape rect)
	: mNoTexture(true)
{
	mRect = rect;

}

bool SpriteNode::isEmpty()
{
	return mEmpty;
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mNoTexture)
		target.draw(mRect);
	else
		target.draw(mSprite, states);
}

