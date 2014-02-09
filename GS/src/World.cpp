#include "World.h"
#include <iostream>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mSceneGraph()
	, mSceneLayers()
	, mTextures()
	, mTilemap()
	, mWorldScale(2.f)
{
	loadTextures();
	loadTileset();
	buildScene();


}

void World::update(sf::Time dt)
{
	
	if (mClickIconTime > sf::Time::Zero)
	{
		mClickIconTime -= dt;
		mClickAlpha = 255 * 
			(mClickIconTime.asMilliseconds() 
			/ static_cast<float>(mClickDuration.asMilliseconds()));
		mClickIcon.setColor(sf::Color(255,255,255,mClickAlpha));
	}
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
	if (mClickIconTime > sf::Time::Zero)
	{
		mWindow.draw(mClickIcon);
	}
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	mTextures.load(Textures::TestTileset, "res/TestTileset.png");	
	mTextures.load(Textures::RedClick, "res/RedClick.png");
	mTilemap.loadTilemap("res/Tilemap.tmx");
}

void World::handleEvent(const sf::Event& event)
{
	sf::Vector2i click;
	click.x = sf::Mouse::getPosition(mWindow).x / (mTilemap.getTileSize().x * static_cast<int>(mWorldScale));
	click.y = sf::Mouse::getPosition(mWindow).y / (mTilemap.getTileSize().y * static_cast<int>(mWorldScale));
	// We're only handling left clicks for now here
	std::cout << "\nClick on Tile ("
		<< click.x
		<< ", "
		<< click.y
		<< ")";
	mClickDuration = sf::seconds(1.f);
	mClickIcon.setPosition(
		static_cast<float>(click.x) * mTilemap.getTileSize().x * mWorldScale, 
		static_cast<float>(click.y) * mTilemap.getTileSize().y * mWorldScale);
	mClickIconTime = mClickDuration;
	mClickAlpha = 255;
}

void World::buildScene()
{
	std::array<std::unique_ptr<SpriteNode>,900> tileSprites;
	int x = 0;

	mClickIcon.setTexture(mTextures.get(Textures::RedClick));
	mClickIcon.setScale(mWorldScale, mWorldScale);

	
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}
	
	/* Build the floor tileset */
	for (int y = 0; y < mTilemap.getWorldSize().y; y++)
	{
		for (int x = 0; x < mTilemap.getWorldSize().x; x++)
		{
			sf::IntRect textureRect = mTilemap.getTextureRect(x, y, "Floor");
			sf::Vector2f worldPos = mTilemap.getWorldPosition(x * mWorldScale,y * mWorldScale);
			sf::Texture& texture = mTilemap.getTexture(x, y, "Floor");
			
			// Since Spritenode is stored as a single array, we need the position relative to
			// its X, Y coordinates--just like the tmx GID number
			int tilePos = x + y * mTilemap.getWorldSize().y;
			
			if (textureRect.left < 0) continue;

			tileSprites[x + y * mTilemap.getWorldSize().y] =
				std::unique_ptr<SpriteNode>(new SpriteNode(texture, textureRect));
			tileSprites[tilePos]->setPosition(worldPos);
			tileSprites[tilePos]->setScale(mWorldScale, mWorldScale);
			mSceneLayers[Floor]->attachChild(std::move(tileSprites[tilePos]));
		}

	}

	/* Build the object tileset */
	for (int y = 0; y < mTilemap.getWorldSize().y; y++)
	{
		for (int x = 0; x < mTilemap.getWorldSize().x; x++)
		{
			sf::IntRect textureRect = mTilemap.getTextureRect(x, y, "Object");
			sf::Vector2f worldPos = mTilemap.getWorldPosition(x * mWorldScale,y * mWorldScale);
			sf::Texture& texture = mTilemap.getTexture(x, y, "Object");
			
			// Since Spritenode is stored as a single array, we need the position relative to
			// its X, Y coordinates--just like the tmx GID number
			int tilePos = x + y * mTilemap.getWorldSize().y;
			
			if (textureRect.left < 0) continue;

			tileSprites[x + y * mTilemap.getWorldSize().y] =
				std::unique_ptr<SpriteNode>(new SpriteNode(texture, textureRect));
			tileSprites[tilePos]->setPosition(worldPos);
			tileSprites[tilePos]->setScale(mWorldScale, mWorldScale);
			mSceneLayers[Object]->attachChild(std::move(tileSprites[tilePos]));
		}

	}

	/*
	// Old Hardcoded tile system
	for (auto& i : mTiles)
	{
		for (auto& iter : i)
		{
			tileSprites[x] = std::unique_ptr<SpriteNode>(new SpriteNode(*iter));
			tileSprites[x]->setPosition(iter->getWorldPosition());
			tileSprites[x]->setScale(2.f, 2.f);
			mSceneLayers[Background]->attachChild(std::move(tileSprites[x]));
			x += 1;
		}
	}
	*/
}

void World::loadTileset()
{
	
	/*
	sf::Vector2i pos(3,0);
	sf::Vector2i size(32,32);
	int count = 0;
	float tileScale = 2.f;
	float x = 0, y = 0;

	for (auto& i : mTiles)
	{
		for (auto& iter : i)
		{
			// get the tile information for this tile in the map
			//sf::Texture& tileTexture;
			sf::Vector2i tileImagePosition;
			sf::Vector2i tileSize;
			
			iter = std::unique_ptr<Tile>(new Tile(mTextures.get(Textures::TestTileset), pos,  size ));
			iter->setWorldPosition(sf::Vector2f(x,y));
			count += 1;
		}
	}
	*/
}

	