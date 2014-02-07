#include "World.h"
#include <iostream>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mSceneGraph()
	, mSceneLayers()
	, mTextures()
	, mTilemap()
{
	loadTextures();
	loadTileset();
	buildScene();


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
	mTilemap.loadTilemap("res/Tilemap.tmx");
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
}

void World::loadTileset()
{
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

}

	