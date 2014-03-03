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
	void setPosition(sf::Vector2i position);
	sf::IntRect getTextureRect();

	/* Tile and sprite positioning utility fns */
	sf::Vector2i getTilePosition();
	void setTilePosition(sf::Vector2i position);
	sf::Vector2i toTilePosition(sf::Vector2i position);
	sf::Vector2i toTilePosition(sf::Vector2f position);
	sf::Vector2f toSpritePosition(sf::Vector2i tilePosition);

protected:

	// Leaving protected for now until we completely decouple this from player
	sf::Sprite mSprite;
	World* mWorld;

private:
	sf::Vector2f mPosition;
	sf::RectangleShape mTextureRect;
	void updateCurrent(sf::Time dt);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif