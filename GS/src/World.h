#ifndef WORLD_H
#define WORLD_H

#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

#include "SceneNode.h"
#include "ResourceManager.h"
#include "SpriteNode.h"
#include "ResourceIdentifiers.h"
#include "CommandQueue.h"
#include "Tileset.h"
#include "Tile.h"

class World
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

	CommandQueue& getCommandQueue();
private:
	enum SceneLayer
	{
		Background,
		Floor,
		Object,
		Sky,
		LayerCount
	};

	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;

	sf::FloatRect mWorldBounds;
	sf::Vector2i mSpawnPosition;

	TextureManager mTextures;
	CommandQueue mCommandQueue;
	std::unique_ptr<Tileset> mTileset;

	void loadTextures();
	void buildScene();
	void loadTileset();

	std::array<std::array<std::unique_ptr<Tile>, 30>, 30> mTileMap;
	

};

#endif
