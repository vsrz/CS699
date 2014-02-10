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
	buildScene();


}

sf::Vector2f World::getWorldScale()
{
	return sf::Vector2f(mWorldScale, mWorldScale);
}
void World::update(sf::Time dt)
{

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
	mTextures.load(Textures::TestTileset, "res/TestTileset.png");	
	mTextures.load(Textures::TestGuy, "res/TestGuy.png");
	mTilemap.loadTilemap("res/Tilemap.tmx");
}

// Return a tile coordinate relative to a pixel coordinate on the screen
sf::Vector2i World::getTilePosition(sf::Vector2i windowPos)
{
	sf::Vector2i position;
	position.x = windowPos.x / 
		(mTilemap.getTileSize().x * mWorldScale);
	position.y = windowPos.y /
		(mTilemap.getTileSize().y * mWorldScale);

	return position;
}

// Return the pixel position of a tile given the position of a pixel
sf::Vector2f World::getPixelPosition(const sf::Vector2i& pixelPos)
{
	sf::Vector2i p = getTilePosition(pixelPos);
	sf::Vector2f position(static_cast<float>(p.x), static_cast<float>(p.y));
		
	position.x = position.x * static_cast<float>(mWorldScale) * mTilemap.getTileSize().x;
	position.y = position.y * static_cast<float>(mWorldScale) * mTilemap.getTileSize().y;
	return position;
}

void World::handleEvent(const sf::Event& event)
{


}

void World::buildScene()
{
	std::array<std::unique_ptr<SpriteNode>,900> tileSprites;
	int x = 0;
	
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

	/* Add the test guy to the screen */
	std::unique_ptr<NpcEntity> player(new NpcEntity(NpcEntity::Type::TestGuy, mTextures));
	mCustomer = player.get();
	mCustomer->setPosition(getPixelPosition(sf::Vector2i(540,160)));
	mCustomer->setVelocity(0.f, 0.f);
	mCustomer->setScale(getWorldScale());
	mSceneLayers[Entity]->attachChild(std::move(player));

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


	