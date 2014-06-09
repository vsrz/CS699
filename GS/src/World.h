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
#include "CashRegisterEntity.h"
#include "ScoreGenerator.h"
#include "AIState.h"

class World
{
public:
	explicit World(sf::RenderWindow& window, TextureManager& textures, ScoreGenerator& score);
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

	ScoreGenerator* getScoreObject();


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

	TextureManager& mTextures;
	FontManager mFonts;
	CommandQueue mCommandQueue;

<<<<<<< HEAD
	// Event handlers and responses
	void displayCollisionOverlay();
	void onMouseButtonClickedEvent(MousePosition mousePosition);
	void onMouseMovedEvent(MousePosition mousePosition);
	void checkMousePosition(MousePosition mousePosition);
	MousePosition mLastMousePosition;
=======
	// AI
	AIState mAiState;
>>>>>>> 2cb0e2a3d37683dfcb2886381d40a5ae2475e70b

	// World objects
	Chairs mChairs;	
	RegisterQueue mRegisterQueue;
	TileLoader mTileLoader;
	Player* mPlayer;
	std::vector<std::unique_ptr<Customer>> mCustomers;
	std::vector<Customer*> mCustomersInScene;
	sf::Time mLastCustomerReleased;
	CashRegister mCashRegister;
	std::unique_ptr<CashRegisterEntity> mCashRegisterIcon;
	int getRemainingWaitingChairs();
	std::vector<std::unique_ptr<ActionAnimator>> mActionAnimations;
	Customer* getCustomerInTile(TilePosition tilePosition); 
	
	// Scene building
	void loadLayer(const char* layerName, unsigned int id);
	size_t getCustomersAllowedInScene(size_t customersInScene);
	void releaseCustomerToScene();
	void updateCustomers(sf::Time dt);
	void buildProps();
	void loadTextures();
	void generateCustomers();
	void buildScene();
	void buildAnimations();
	void attachHeartDisplay(Customer* customer);
	void attachStatusDisplay(Customer* customer);

	// Scoring
	ScoreGenerator& mScore;

};

#endif
