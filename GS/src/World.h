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
#include "Tile.h"
#include "Tilemap.h"
#include "Player.h"
#include "Aircraft.h"

class Player;

class World
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

	sf::Vector2i getTilePosition(sf::Vector2i windowPos);
	sf::Vector2f getPixelsFromTilePosition(const sf::Vector2i& tilePos);
	sf::Vector2f getPixelPosition(const sf::Vector2i& tilePos);
	sf::Vector2f getWorldScale();
	
	void handleEvent(const sf::Event& event);
	CommandQueue& getCommandQueue();
private:
	enum SceneLayer
	{
		Background,
		Floor,
		Object,
		Entity,
		Gui,
		LayerCount
	};

	sf::Vector2f mWorldScale;
	
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;

	sf::FloatRect mWorldBounds;
	sf::Vector2i mSpawnPosition;

	TextureManager mTextures;
	CommandQueue mCommandQueue;

	void loadTextures();
	void buildScene();

	std::array<std::array<std::unique_ptr<Tile>, 20>, 12> mTiles;
	Tilemap mTilemap;

	Player* mPlayer;

	
};

#endif
