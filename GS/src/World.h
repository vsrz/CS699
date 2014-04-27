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
#include "Customer.h"
#include "World.h"
#include "ChairEntity.h"
#include "RegisterQueue.h"
#include "ActionAnimator.h"
#include "CashRegister.h"

class World
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

	sf::Vector2f getWorldScale();
	std::vector<ChairEntity*> getChairs(ChairEntity::Type chairType);

	int getTileIndex(int x, int y);
	void handleEvent(const sf::Event& event);
	CommandQueue& getCommandQueue();
	Tilemap mTilemap;

	RegisterQueue* getQueue();

	bool isRegisterLineFull();
	TilePosition getPlayerPosition();
	std::vector<Customer*> getCustomers();

	// Scoring
	int mAngryCustomers;
	int mCustomersServed;
	int mTipsMade;
	int mTotalCash;

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

	// World objects
	std::vector<std::unique_ptr<ChairEntity>> mChairs;	
	RegisterQueue mRegisterQueue;
	TileLoader mTileLoader;
	Player* mPlayer;
	std::vector<std::unique_ptr<Customer>> mCustomers;
	sf::Time mLastCustomerReleased;
	CashRegister mCashRegister;
	int getRemainingWaitingChairs();
	std::vector<std::unique_ptr<ActionAnimator>> mActionAnimations;
	
	// Scene building
	void loadLayer(const char* layerName, unsigned int id);
	void updateCustomers(sf::Time dt);
	void buildProps();
	void loadTextures();
	void addCustomers();
	void buildScene();
	void buildAnimations();
	void attachHeartDisplay(Customer* customer);
	void attachStatusDisplay(Customer* customer);

};

#endif
