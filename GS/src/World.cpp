#include "World.h"
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <algorithm>
#include "Glob.h"
#include "ChairEntity.h"
#include "DoorEntity.h"
#include "PetEntity.h"
#include "HeartEntity.h"
#include "StatusNotifierEntity.h"
#include "ScoreDisplay.h"
#include "AIState.h"

World::World(sf::RenderWindow& window, TextureManager& textures, ScoreGenerator& score)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTilemap(	static_cast<int>(Config::WORLD_WIDTH), 
				static_cast<int>(Config::WORLD_HEIGHT), 
				Config::TILE_WIDTH, 
				Config::TILE_HEIGHT,
				Config::WORLD_SCALE)
	, mTextures(textures)
	, mScore(score)
	, mAiState()
{
	initalize();
}

void World::initalize()
{
	mWorldScale = sf::Vector2f(Config::WORLD_SCALE, Config::WORLD_SCALE);
	mLastMousePosition = MousePosition(0.f, 0.f);
	loadTextures();
	mFonts.load(Fonts::ID::Bit, "res/8b.ttf");
	buildScene();
	mAiState.setWorld(this);


}

sf::Vector2f World::getWorldScale()
{
	return mWorldScale;
}


void World::update(sf::Time dt)
{
	// First, Z-sort all customers
	mSceneLayers[Entity]->sortChildren();
	
	// Scene graph update
	mSceneGraph.update(dt);
	
	// Normal scene update for each customer
	updateCustomers(dt);
	
	// Check if the mouse is resting on a customer
	checkMousePosition(mLastMousePosition);

	mAiState.update(dt);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);

}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

ScoreGenerator* World::getScoreObject()
{
	return &mScore;
}

TilePosition World::getPlayerPosition()
{
	return mPlayer->getTilePosition();
}

void World::loadTextures()
{	
	mTileLoader.loadFromFile(Config::TILEMAP_FILENAME);
}

std::vector<ChairEntity*> World::getChairs(ChairEntity::Type chairType)
{
	std::vector<ChairEntity*> chairs;
	for (auto& i : mChairs)
	{
		if (i.get()->getChairType() == chairType || chairType == ChairEntity::Type::All)
		{
			chairs.push_back(i.get());
		}
	}
	return chairs;
}

// Returns the mTiles index ID using the x,y coordinate of 
int World::getTileIndex(int x, int y)
{
	return mTileLoader.getTileNumber(x,y);
}

// Overlays the current scene with a collision overlay
void World::displayCollisionOverlay()
{
	std::unique_ptr<SpriteNode> tile;

	for (int y = 0; y < mTileLoader.getWorldSize().y; y++)
	{
		for (int x = 0; x < mTileLoader.getWorldSize().x; x++)
		{
			sf::RectangleShape rect(sf::Vector2f(
				static_cast<float>(mTileLoader.getTileSize().x * mWorldScale.x),
				static_cast<float>(mTileLoader.getTileSize().y * mWorldScale.y))
				);
			rect.setPosition(x * mWorldScale.x * mTileLoader.getTileSize().x
				, y * mWorldScale.y * mTileLoader.getTileSize().y);
			rect.setFillColor(sf::Color(0, 128, 0, 50));
			if (mTilemap.isTileOccupied(x, y)) rect.setFillColor(sf::Color(128, 0, 0, 50));

			tile = std::unique_ptr<SpriteNode>(new SpriteNode(rect));
			mSceneLayers[Debug]->attachChild(std::move(tile));
		}
	}
}

void World::onMouseButtonClickedEvent(MousePosition mousePosition)
{
	extern std::map<std::string, std::string> g_debugData;

	// Update some debug tile stuff
	TilePosition mouseTilePosition = toTilePosition(mousePosition);

	g_debugData["TileNum"] = toString(mTileLoader.getTileNumber(static_cast<int>(mouseTilePosition.x), static_cast<int>(mouseTilePosition.y)));
	g_debugData["TileData"] = toString(mTilemap.getTileProperty(snapToSpritePosition(mousePosition)));
	g_debugData["TilePos"] = toString(mouseTilePosition.x) + "," + toString(mouseTilePosition.y);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		TilePosition clickedTile = toTilePosition(mousePosition);
		// Find out if the tile clicked was a chair
		for (auto& chair : mChairs)
		{
			if (chair->getChairPosition() == clickedTile || chair->getAltClickPosition() == clickedTile)
			{
				/* TODO: convert alt clicked tile */
				//if (chair->getAltClickPosition() == clickedTile)
				//{
				//	clickedTile
				//}
				// Waiting room case
				if (chair->getChairType() == ChairEntity::Waiting)
				{
					// If the chair is occupied, call customerClicked() for the customer in the chair
					if (chair->isOccupied())
					{
						Customer* customer;
						customer = chair->getOccupant();
						customer->customerClicked();
						return;
					}

					// If it's not occupied, just go to the staging area position
					else
					{
						if (mPlayer->getState() == Player::State::Busy)
							return;
						mPlayer->moveToTile(chair->getStagingPosition());
						return;
					}
				}

				// If it's not a waiting chair
				else
				{
					// TODO: washing station queue processing
					if (mPlayer->getTilePosition() == chair->getOperatingPosition())
					{
						Customer* cust = chair->getOccupant();
						if (cust != nullptr)
						{
							if (cust->isSitting() &&
								!cust->isWaitingToMoveToStation() &&
								mPlayer->getState() != Player::State::Busy)
							{
								mPlayer->useStation(chair.get());
							}
							else
								cust->customerClicked();
						}
						return;
					}

					// They are not standing in this chair's operating position, move there
					else
					{
						// If the chair is occupied and a customer is waiting to move to the next
						// station, move them, otherwise move to its operating position
						bool clicked = false;
						if (chair->isOccupied())
						{
							if (chair->getOccupant()->isWaitingToMoveToStation())
							{
								clicked = true;
								chair->getOccupant()->customerClicked();
							}
						}
						if (!clicked && mPlayer->getState() != Player::Busy)
							mPlayer->moveToTile(chair->getOperatingPosition());

						return;
					}
				}
			}
		}

		// Find out if we clicked the cash regsiter
		for (auto& cReg : mCashRegister.getTilePositions())
		{
			if (mPlayer->getState() == Player::State::Busy)
				return;
			if (cReg == clickedTile)
			{
				TilePosition opPos = Config::RegisterQueue::OPERATING_POSITION[0];
				// If we're already standing in the operation position, operate the register
				if (mPlayer->getTilePosition() == opPos)
				{
					if (!mRegisterQueue.isEmpty())
					{
						mPlayer->useRegister(&mRegisterQueue);
					}
					return;
				}

				// Otherwise, move to the operating position
				else
				{
					mPlayer->moveToTile(opPos);
					return;
				}
			}

		}
		if (mPlayer->getState() == Player::State::Busy)
			return;

		mPlayer->moveToTile(toTilePosition(mousePosition));
#ifdef DEBUG
		g_debugData["Destination:"] = toString(mousePosition.x) + "," + toString(mousePosition.y);
#endif
	}
}

Customer* World::getCustomerInTile(TilePosition tilePosition)
{
	// This is a hack. Since the customers are always two tiles tall, we'll grab them
	// from either the origin tile or the one directly above
	for (auto& it = mCustomersInScene.begin(); it != mCustomersInScene.end(); ++it)
	{
		Customer* cust = *it;
		TilePosition tp = cust->getTilePosition();
		if (tp.x == tilePosition.x &&
			(tp.y == tilePosition.y || tp.y - 1 == tilePosition.y))
		{
			return cust;
		}
	}

	return nullptr; 

}

void World::checkMousePosition(MousePosition mousePosition)
{
	TilePosition mouseOverTile = toTilePosition(mousePosition);
	Customer* cust = getCustomerInTile(mouseOverTile);

	if (cust != nullptr)
	{
		if (cust->isClickable())
		{
			cust->highlightCustomer();
		}
	}
}

void World::onMouseMovedEvent(MousePosition mousePosition)
{
	mLastMousePosition = mousePosition;

}

void World::handleEvent(const sf::Event& event)
{
	MousePosition mousePosition = sf::Mouse::getPosition(mWindow);
	
	// Mouse button clicks
	if (event.type == sf::Event::MouseButtonPressed)
	{
		onMouseButtonClickedEvent(mousePosition);
	}

	// Mouse movement
	else if (event.type == sf::Event::MouseMoved)
	{
		onMouseMovedEvent(mousePosition);
	}

#ifdef DEBUG
	// Special debugging keyboard presses
	/* Pressing F4 brings up a collision overlay */
	else if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::F4)
	{
		displayCollisionOverlay();
	}

	/* Pressing F5 immediately ends the game */
	else if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::F5)
	{
		getScoreObject()->addServed(Config::TOTAL_CUSTOMERS);
	}

#endif

	else
	{
		// Other uncaught event
	}

}

/* Loads a layer of the world from the tilemap. The layer must exist in the Tilemap datafile */
void World::loadLayer(const char* layerName, unsigned int id)
{

	std::unique_ptr<SpriteNode> tile;

	for (int y = 0; y < mTileLoader.getWorldSize().y; y++)
	{
		for (int x = 0; x < mTileLoader.getWorldSize().x; x++)
		{
			sf::IntRect textureRect = mTileLoader.getTextureRect(x, y, layerName);
			sf::Vector2f worldPos = mTileLoader.getWorldPosition(x * static_cast<int>(mWorldScale.x) ,y * static_cast<int>(mWorldScale.y));
			sf::Texture& texture = mTileLoader.getTexture(x, y, layerName);

			// Since Spritenode is stored as a single array, we need the position relative to
			// its X, Y coordinates--just like the tmx GID number
			int tilePos = x + y * mTileLoader.getWorldSize().y;
			
			if (textureRect.left < 0) continue;

			tile = std::unique_ptr<SpriteNode>(new SpriteNode(texture, textureRect));
			tile->setPosition(worldPos);
			tile->setScale(mWorldScale);
			if (id == SceneLayer::ObjectBlocking || id == SceneLayer::IntermediateBlocking)
			{
				mTilemap.setTileProperty(x, y, Tiles::Property::Occupied);
			}
			mSceneLayers[id]->attachChild(std::move(tile));
		}
	}
}

void World::buildProps()
{
	int index = 0;
	
	/* Waiting room chairs */
	for (auto& i : Config::Chairs::SEATING_POSITION)
	{
		std::unique_ptr<ChairEntity> c(new ChairEntity(i,  this));
		c->setChairPosition(Config::Chairs::SEATING_POSITION[index]);
		c->setStagingPosition(Config::Chairs::STAGING_POSITION[index]);
		c->setOperatingPosition(Config::Chairs::OPERATING_POSITION[index]);
		c->setDirection(Config::Chairs::SEATING_DIRECTION[index]);
		c->setChairType(static_cast<ChairEntity::Type>(Config::Chairs::TYPE[index++]));
		mChairs.push_back(std::move(c));

	}

	/* Walk in door */
	std::unique_ptr<DoorEntity> f(new DoorEntity(mTextures, this));
	mSceneLayers[Entity]->attachChild(std::move(f));

}

void World::generateCustomers()
{	
	Prng rand;
	std::array<unsigned int, Config::TOTAL_CUSTOMERS> customers;
	unsigned int last = 99;
	
	customers[14] = Customer::Type::WomanTeen;
	customers[13] = Customer::Type::WomanMiddle;
	customers[12] = Customer::Type::ManTeen;
	customers[11] = Customer::Type::ManYoung;
	customers[10] = Customer::Type::WomanOld;
	customers[9] = Customer::Type::ManMidage;
	customers[8] = Customer::Type::WomanTeen;
	customers[7] = Customer::Type::WomanMiddle;
	customers[6] = Customer::Type::ManTeen;
	customers[5] = Customer::Type::ManYoung;
	customers[4] = Customer::Type::WomanOld;
	customers[3] = Customer::Type::ManMidage;
	customers[2] = Customer::Type::WomanTeen;
	customers[1] = Customer::Type::WomanMiddle;
	customers[0] = Customer::Type::ManTeen;
	
	// Generate customers statically for now, we want to reduce the repetiveness
	// until we have more textures to work with
	/* 
	for (int i = 0; i < Config::TOTAL_CUSTOMERS; i++)
	{
		// Try not to get two of the same customers in a row
		do
		{
			num = rand.getRand(0,Customer::Type::Count-1);
		} while (num == last);
		last = num;
		customers[i] = num;
	}
	*/

	for (int i = 0; i < Config::TOTAL_CUSTOMERS; ++i)
	{
		std::unique_ptr<Customer> cust(new Customer(mTextures, this, customers[i]));
		if (i == 14)
		{
			unsigned int needs = Customer::Needs::Wash | Customer::Needs::Cut;
			cust.get()->setNeeds(needs);
			cust.get()->addToPatience(sf::seconds(60.f));
			cust.get()->setPatience(200.f);
		}
		else if (i == 13)
		{
			unsigned int needs = Customer::Needs::Wash | Customer::Needs::Cut | Customer::Needs::Color;
			cust.get()->setNeeds(needs);

		}
		mCustomers.push_back(std::move(cust));
	}
}

std::vector<Customer*> World::getCustomers()
{
	std::vector<Customer*> cPtrs;
	for (size_t i = 0; i < mCustomers.size(); i++)
	{
		if (mCustomers[i].get()->isMoving())
			cPtrs.push_back(mCustomers[i].get());
	}
	return cPtrs;
}


void World::buildAnimations()
{
	/**
	 * Probably should config file this stuff at a later time
	 */
	std::unique_ptr<ActionAnimator> anim = 
		std::unique_ptr<ActionAnimator>(new ActionAnimator(mTextures, this, ActionAnimator::Type::Wash, mPlayer));
	anim.get()->setAnimationLocation(TilePosition(18,7));
	anim.get()->setTriggerTile(TilePosition(18,7));
	mSceneLayers[ObjectDecorative]->attachChild(std::move(anim));

	anim = std::unique_ptr<ActionAnimator>(new ActionAnimator(mTextures, this, ActionAnimator::Type::Wash, mPlayer));
	anim.get()->setAnimationLocation(TilePosition(18,9));
	anim.get()->setTriggerTile(TilePosition(18,9));
	mSceneLayers[ObjectDecorative]->attachChild(std::move(anim));

	anim = std::unique_ptr<ActionAnimator>(new ActionAnimator(mTextures, this, ActionAnimator::Type::Cut, mPlayer));
	anim.get()->setAnimationLocation(TilePosition(16,4));
	anim.get()->setTriggerTile(TilePosition(15,5));
	mSceneLayers[ObjectDecorative]->attachChild(std::move(anim));

	anim = std::unique_ptr<ActionAnimator>(new ActionAnimator(mTextures, this, ActionAnimator::Type::Cut, mPlayer));
	anim.get()->setAnimationLocation(TilePosition(18,4));
	anim.get()->setTriggerTile(TilePosition(19,5));
	mSceneLayers[ObjectDecorative]->attachChild(std::move(anim));

	anim = std::unique_ptr<ActionAnimator>(new ActionAnimator(mTextures, this, ActionAnimator::Type::Color, mPlayer));
	anim.get()->setAnimationLocation(TilePosition(10,7));
	anim.get()->setTriggerTile(TilePosition(10,9));
	mSceneLayers[ObjectDecorative]->attachChild(std::move(anim));

	anim = std::unique_ptr<ActionAnimator>(new ActionAnimator(mTextures, this, ActionAnimator::Type::Color, mPlayer));
	anim.get()->setAnimationLocation(TilePosition(12,7));
	anim.get()->setTriggerTile(TilePosition(12,9));
	mSceneLayers[ObjectDecorative]->attachChild(std::move(anim));

}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}
	
	loadLayer("Floor", SceneLayer::Floor);
	loadLayer("IntermediateBlocking", SceneLayer::IntermediateBlocking);
	loadLayer("IntermediateDecorative", SceneLayer::IntermediateDecorative);
	loadLayer("ObjectBlocking", SceneLayer::ObjectBlocking);
	loadLayer("ObjectDecorative", SceneLayer::ObjectDecorative);
	
	/* Add a test player to the screen */
	std::unique_ptr<Player> player(new Player(mTextures, this));
	mPlayer = player.get();
	mSceneLayers[Entity]->attachChild(std::move(player));

	/* Add the pet */
	std::unique_ptr<PetEntity> pet(new PetEntity(mTextures, this));
	mSceneLayers[Entity]->attachChild(std::move(pet));

	/* Initialize the chairs */
	buildProps();

	/* Build the customer queue */
	generateCustomers();

	/* Initialize the animations */
	buildAnimations();

	/* Put up the scoreboard */
	std::unique_ptr<ScoreDisplay> score = std::unique_ptr<ScoreDisplay>(new ScoreDisplay(getScoreObject(), mFonts.get(Fonts::Bit)));
	mSceneLayers[Gui]->attachChild(std::move(score));

	/* Add the register icon to the scene */
	std::unique_ptr<CashRegisterEntity> cash = std::unique_ptr<CashRegisterEntity>(new CashRegisterEntity(mTextures, this, &mRegisterQueue));
	mSceneLayers[Gui]->attachChild(std::move(cash));
}

int World::getRemainingWaitingChairs()
{
	int total = 5;
	for (auto& chairs : mChairs)
	{
		if (chairs->getChairType() == ChairEntity::Type::Waiting && chairs->isOccupied())
			total--;
	}
	return total;
}

/* Attaches a heart display to the customer object */
void World::attachHeartDisplay(Customer* customer)
{
	std::unique_ptr<HeartEntity> hearts = std::unique_ptr<HeartEntity>(new HeartEntity(mTextures, this, customer));
	mSceneLayers[Gui]->attachChild(std::move(hearts));
}

void World::attachStatusDisplay(Customer* customer)
{
	std::unique_ptr<StatusNotifierEntity> stat = std::unique_ptr<StatusNotifierEntity>(new StatusNotifierEntity(mTextures, this, customer));
	mSceneLayers[Gui]->attachChild(std::move(stat));
}

size_t World::getCustomersAllowedInScene(size_t customersInScene)
{

#ifdef DEBUG
	// Useful for testing
	return 15;
#endif
	
	// This is so that customers are trickled in the early stage
	// They begin to bum rush you halfway through the game
	switch (customersInScene)
	{
	case 15:
	case 14:
		return 1;
	case 13:
		return 2;
	case 12:
	case 11:
		return 4;
	case 10:
	case 9:
	case 8:
		return 6;
	case 7:
	case 6:
	default:
		return 15;
	}
}

void World::releaseCustomerToScene()
{
	std::unique_ptr<Customer> customer = std::move(mCustomers.back());
	mCustomersInScene.push_back(customer.get());
	attachHeartDisplay(customer.get());
	attachStatusDisplay(customer.get());
	mSceneLayers[Entity]->attachChild(std::move(customer));
	mCustomers.pop_back();

	/*  Takes care of a rendering order issue when a
	first enters the scene */
	mSceneLayers[Entity]->sortChildren();
	mLastCustomerReleased = sf::Time::Zero;
}

/* Update the customer stack and release a customer if necessary */
void World::updateCustomers(sf::Time dt)
{
	// Count the number of customers in the scene
	size_t customersInScene = 0;
	for (auto& it = mCustomersInScene.begin(); it != mCustomersInScene.end(); ++it)
	{
		Customer* cust = *it;
		if (cust->getState() != CustomerState::Delete)
			customersInScene++;
	}

	// Get the number of customers allowed in the scene at once
	size_t customersAllowedInScene = getCustomersAllowedInScene(customersInScene);
	
	mLastCustomerReleased += dt;
	
	// If the release interval has elapsed and there's room, try to release a new customer
	if (mLastCustomerReleased > sf::seconds(Config::Customer::RELEASE_INTERVAL) &&
		getRemainingWaitingChairs() > 0 &&
		customersAllowedInScene > customersInScene &&
		mCustomers.size() > 0)
	{
		size_t remainingCustomers = mCustomers.size();
		releaseCustomerToScene();
	}

	/* TODO: Check the scene for any customers that need to be removed */

}

RegisterQueue* World::getQueue()
{
	return &mRegisterQueue;
}

