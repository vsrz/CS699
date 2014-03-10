#include "World.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "Glob.h"
#include "ChairEntity.h"
#include "DoorEntity.h"

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTilemap(Config::WORLD_WIDTH, Config::WORLD_HEIGHT, Config::TILE_WIDTH, Config::TILE_HEIGHT, Config::WORLD_SCALE)
{
	initalize();
	loadTextures();
	buildScene();	


}

void World::initalize()
{
	mWorldScale = sf::Vector2f(Config::WORLD_SCALE, Config::WORLD_SCALE);

}

sf::Vector2f World::getWorldScale()
{
	return mWorldScale;
}


void World::update(sf::Time dt)
{
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

void World::loadTextures()
{
	mTextures.load(Textures::TestGuy, "res/TestGuy.png");
	mTextures.load(Textures::TestTileset, "res/TestTileset.png");
	mTextures.load(Textures::ManOveralls, "res/man01.png");
	mTextures.load(Textures::AutoDoors, "res/doors02.png");
	mTileLoader.loadFromFile(Config::TILEMAP_FILENAME);
}

// Return a tile coordinate relative to a pixel coordinate on the screen
sf::Vector2i World::getTilePosition(sf::Vector2i windowPos)
{
	sf::Vector2i position;
	position.x = windowPos.x / 
		(mTileLoader.getTileSize().x * mWorldScale.x);
	position.y = windowPos.y /
		(mTileLoader.getTileSize().y * mWorldScale.y);

	return position;
}

// Return the pixel position given a tile coordinate
sf::Vector2f World::getPixelsFromTilePosition(const sf::Vector2i& tilePos)
{
	return sf::Vector2f(
		static_cast<float>(tilePos.x * mWorldScale.x * mTileLoader.getTileSize().x),
		static_cast<float>(tilePos.y * mWorldScale.y * mTileLoader.getTileSize().y)
		);
}

// Returns the mTiles index ID using the x,y coordinate of 
int World::getTileIndex(int x, int y)
{
	return mTileLoader.getTileNumber(x,y);
}

// Return the pixel position of a tile given the position of a pixel
sf::Vector2f World::getPixelPosition(const sf::Vector2i& pixelPos)
{
	sf::Vector2i p = getTilePosition(pixelPos);
	sf::Vector2f position(static_cast<float>(p.x), static_cast<float>(p.y));
		
	position.x = position.x * mWorldScale.x * mTileLoader.getTileSize().x;
	position.y = position.y * mWorldScale.y * mTileLoader.getTileSize().y;
	return position;
}

void World::handleEvent(const sf::Event& event)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	sf::Vector2i mouseTilePosition = getTilePosition(mousePosition);
	if (event.type == sf::Event::MouseButtonPressed)
	{
		#ifdef DEBUG
		extern std::map<std::string, std::string> g_debugData;

		// Update some debug tile stuff
		g_debugData["TileNum"] = toString(mTileLoader.getTileNumber(mouseTilePosition.x, mouseTilePosition.y));
		g_debugData["TileData"] = toString(mTilemap.getTileProperty(mousePosition));
		g_debugData["TilePos"] = toString(mouseTilePosition.x) + "," + toString(mouseTilePosition.y);
		#endif
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mPlayer->moveToTile(mousePosition);
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
	for (auto& i : Config::Chairs::WAITING_CHAIR_POSITIONS)
	{
		std::unique_ptr<ChairEntity> c(new ChairEntity(i,  this));
		mWaitingChairs[index++] = std::move(c);
	}

	/* Walk in door */
	std::unique_ptr<DoorEntity> f(new DoorEntity(mTextures, this));
	mSceneLayers[ObjectDecorative]->attachChild(std::move(f));

}

void World::addCustomer(unsigned int customerType)
{
	for (int i = 0; i < 5; ++i)
	{
		std::unique_ptr<Customer> cust(new Customer(mTextures, this, customerType));
		mCustomers.push(std::move(cust));
	}
	
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

	/* Initialize the chairs */
	buildProps();

	/* Build the customer queue */
	addCustomer(Player::ID::ManOveralls);
}

/* Update the customer stack and release a customer if necessary */
void World::updateCustomers(sf::Time dt)
{
	mLastCustomerReleased += dt;
	if (mLastCustomerReleased > sf::seconds(Config::Customer::RELEASE_INTERVAL))
	{
		// If there are any customers left, add one to the scene node
		if (mCustomers.size() > 0)
		{
			mSceneLayers[Entity]->attachChild(std::move(mCustomers.top()));
			mCustomers.pop();
		}
		mLastCustomerReleased = sf::Time::Zero;
	}
}


