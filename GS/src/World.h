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
#include "TileLoader.h"
#include "Player.h"
#include "World.h"
#include "ChairEntity.h"

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
	int getTileIndex(int x, int y);
	void handleEvent(const sf::Event& event);
	CommandQueue& getCommandQueue();
	Tilemap mTilemap;
	
private:
	enum SceneLayer
	{
		Background,
		Floor,
		IntermediateBlocking,
		IntermediateDecorative,
		ObjectBlocking,
		Entity,
		ObjectDecorative,
		Gui,
		Debug,
		LayerCount
	};

	void initalize();
	sf::Vector2f mWorldScale;
	
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	
	/* Scene Graph builds the drawable world */
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;

	sf::FloatRect mWorldBounds;
	sf::Vector2i mSpawnPosition;

	TextureManager mTextures;
	CommandQueue mCommandQueue;

	std::array<std::unique_ptr<ChairEntity>, 5u> mWaitingChairs;
	void loadLayer(const char* layerName, unsigned int id);
	void buildProps();
	void loadTextures();
	void addCustomer(unsigned int customerType);
	void buildScene();

	TileLoader mTileLoader;
	Player* mPlayer;
	std::stack<std::unique_ptr<Player>> mCustomers;
	std::vector<std::unique_ptr<Player>> mActiveCustomers;
	sf::Time mLastCustomerReleased;
	void updateCustomers(sf::Time dt);

};

#endif
