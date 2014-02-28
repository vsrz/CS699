#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class World;

class Entity
{
public:
	Entity(World *mWorld, float speed);
	virtual ~Entity();

	/* Properties */
	void setSpeed(float speed);
	float getSpeed();
	void setSprite(sf::Sprite &sprite);
	sf::Vector2i getCurrentTilePosition();

	/* Tile and sprite positioning utility fns */
	sf::Vector2i toTilePosition(sf::Vector2i position);
	sf::Vector2i toTilePosition(sf::Vector2f position);
	sf::Vector2f toSpritePosition(sf::Vector2i tilePosition);

protected:

	void update(sf::Time dt);
	void draw();

private:
	World* mWorld;
	float mSpeed;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;

};

#endif