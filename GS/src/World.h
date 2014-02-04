#ifndef WORLD_H
#define WORLD_H

#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>

#include "SceneNode.h"
#include "ResourceManager.h"
#include "SpriteNode.h"
#include "ResourceIdentifiers.h"
#include "Aircraft.h"
#include "CommandQueue.h"

class World
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

	CommandQueue& getCommandQueue();

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};

	void loadTextures();
	void buildScene();

	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;

	TextureManager mTextures;
	
	Aircraft* mPlayerAircraft;

	CommandQueue mCommandQueue;

	void adaptPlayerPosition();
	void adaptPlayerVelocity();

};

#endif

