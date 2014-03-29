/**
 * Entity.H
 * Handles postiion and drawing of a sprite in the game world.
 * Implements all the tile position to sprite position functions
 * so you only have to deal with tile positions when manipulating
 * a sprite.
 **/
  

#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "SceneNode.h"
#include "Glob.h"

class World;

class Entity
	: public SceneNode
{
public:

	Entity(World *mWorld);
	virtual ~Entity();

	/* Game Properties */

	/* Sprite manipulation */
	void setSprite(sf::Sprite &sprite);
	void setTextureRect(sf::IntRect rect);
	void setTilePosition(TilePosition position);
	void setPosition(SpritePosition position);
	sf::IntRect getTextureRect();

	/* Tile and sprite positioning utility fns */
	sf::Vector2f getTilePosition();
	void setTilePosition(sf::Vector2i position);


protected:

	// Leaving protected for now until we completely decouple this from player
	sf::Sprite mSprite;
	World* mWorld;

private:
	sf::RectangleShape mTextureRect;
	void updateCurrent(sf::Time dt);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	float getZPosition();

};

#endif