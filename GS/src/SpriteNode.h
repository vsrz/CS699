#ifndef SPRITENODE_H
#define SPRITENODE_H

#pragma once

#include "SceneNode.h"
#include <SFML/Graphics.hpp>
#include "Tile.h"

class SpriteNode
	: public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(sf::Sprite sprite);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
	SpriteNode(Tile& tile);
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite mSprite;

};

#endif
