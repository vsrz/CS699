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

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTilemap(Config::WORLD_WIDTH, Config::WORLD_HEIGHT, Config::TILE_WIDTH, Config::TILE_HEIGHT, Config::WORLD_SCALE)
	, mScore()
{
	initalize();
}

void World::initalize()
{
	mWorldScale = sf::Vector2f(Config::WORLD_SCALE, Config::WORLD_SCALE);
	loadTextures();
	mFonts.load(Fonts::ID::Bit, "res/8b.ttf");
	buildScene();
}

sf::Vector2f World::getWorldScale()
{
	return mWorldScale;
}


void World::update(sf::Time dt)
{
	mSceneLayers[Entity]->sortChildren();
	mSceneGraph.update(dt);
	updateCustomers(dt);

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
	mTextures.load(Textures::TestGuy, "res/TestGuy.png");
	mTextures.load(Textures::WomanTeen01, "res/woman_teen_01.png");
	mTextures.load(Textures::WomanMidage01, "res/woman_midage_01.png");
	mTextures.load(Textures::WomanOld01, "res/woman_old_01.png");
	mTextures.load(Textures::ManYoung01, "res/man_young_01.png");
	mTextures.load(Textures::ManTeen01, "res/man_teen_01.png");
	mTextures.load(Textures::ManOveralls, "res/man01.png");
	mTextures.load(Textures::AutoDoors, "res/doors02.png");
	mTextures.load(Textures::Kitty, "res/feline_01.png");
	mTextures.load(Textures::AnimWash, "res/anim_wash_01.png");
	mTextures.load(Textures::AnimCut, "res/anim_cut_01.png");
	mTextures.load(Textures::AnimColor, "res/anim_color_01.png");
	mTextures.load(Textures::Hearts, "res/hearts_02.png");
	mTextures.load(Textures::StatusNotifiers, "res/notifiers_02.png");
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


void World::handleEvent(const sf::Event& event)
{
	MousePosition mousePosition = sf::Mouse::getPosition(mWindow);
	TilePosition mouseTilePosition = toTilePosition(mousePosition);
	if (event.type == sf::Event::MouseButtonPressed)
	{
#ifdef DEBUG
		extern std::map<std::string, std::string> g_debugData;

		// Update some debug tile stuff
		g_debugData["TileNum"] = toString(mTileLoader.getTileNumber(mouseTilePosition.x, mouseTilePosition.y));
		g_debugData["TileData"] = toString(mTilemap.getTileProperty(snapToSpritePosition(mousePosition)));
		g_debugData["TilePos"] = toString(mouseTilePosition.x) + "," + toString(mouseTilePosition.y);
#endif
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			TilePosition clickedTile = toTilePosition(mousePosition);
			// Find out if the tile clicked was a chair
			for (auto& chair : mChairs)
			{
				if (chair->getChairPosition() == clickedTile)
				{
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

	#ifdef DEBUG
	/* Pressing F4 brings up a collision overlay */
	else if (event.type == sf::Event::KeyPressed && 
		event.key.code == sf::Keyboard::F4)
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
				rect.setFillColor(sf::Color(0,128,0,50));
				if (mTilemap.isTileOccupied(x,y)) rect.setFillColor(sf::Color(128,0,0,50));
			
				tile = std::unique_ptr<SpriteNode>(new SpriteNode(rect));
				mSceneLayers[Debug]->attachChild(std::move(tile));
			}
		}
	}
	#endif
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
			sf::Vector2f worldPos = mTileLoader.getWorldPosition(x * mWorldScale.x ,y * mWorldScale.y);
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
	int num;
	
	for (int i = 0; i < Config::TOTAL_CUSTOMERS; i++)
	{
		// Try not to get two of the same customers in a row
		do
		{
			num = rand.getRand(0,Customer::Type::Count-1);
		} while (num == last);
		std::cout<<num<<std::endl;
		last = num;
		customers[i] = num;
	}
	
	for (int i = 0; i < Config::TOTAL_CUSTOMERS; ++i)
	{
		std::unique_ptr<Customer> cust(new Customer(mTextures, this, customers[i]));
		mCustomers.push_back(std::move(cust));
	}
}

std::vector<Customer*> World::getCustomers()
{
	std::vector<Customer*> cPtrs;
	for (int i = 0; i < mCustomers.size(); i++)
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


/* Update the customer stack and release a customer if necessary */
void World::updateCustomers(sf::Time dt)
{
	mLastCustomerReleased += dt;
	if (mLastCustomerReleased > sf::seconds(Config::Customer::RELEASE_INTERVAL) && 
		getRemainingWaitingChairs() > 0)
	{
		// If there are any customers left, add one to the scene node
		if (mCustomers.size() > 0)
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

		}
		mLastCustomerReleased = sf::Time::Zero;
	}

	/* Check the scene for any customers that need to be removed */
	//for (auto& cust

}

RegisterQueue* World::getQueue()
{
	return &mRegisterQueue;
}

