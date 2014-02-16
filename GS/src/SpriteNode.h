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
	SpriteNode();
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(sf::Sprite sprite);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
	SpriteNode(const sf::RectangleShape rect);
	SpriteNode(Tile& tile);
	bool isEmpty();
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite mSprite;
	bool mEmpty;
	bool mNoTexture;
	sf::RectangleShape mRect;
};

#endif
