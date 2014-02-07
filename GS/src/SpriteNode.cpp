#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
{

}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
	: mSprite(texture, rect)
{

}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}


SpriteNode::SpriteNode(Tile& tile)
	: mSprite(tile.getTexture(), tile.getTextureRect())
{
	
}
