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
		LayerCount
	};

	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;

	sf::FloatRect mWorldBounds;
	sf::Vector2i mSpawnPosition;

	ImageManager mImages;
	TextureManager mTextures;
	CommandQueue mCommandQueue;
	Tileset mTileset;

	void loadTextures();
	void buildScene();
	void loadTileset();

	std::array<std::array<Tile*, 30>, 30> mTileMap;
	

};

#endif
