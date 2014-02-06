#include "World.h"
#include <iostream>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mSceneGraph()
	, mSceneLayers()
	, mTextures()

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
	for (auto& row : mTileMap)
	{
		for (auto& col : row)
		{
			col->draw(mWindow);
		}
	}
	
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	mTextures.load(Textures::TestTileset, "res/TestTileset.png");
}

void World::buildScene()
{
}

void World::loadTileset()
{
	std::unique_ptr<Tileset> mTileset(new Tileset(mTextures.get(Textures::TestTileset)));

	for (auto& row : mTileMap)
	{
		for (auto& col : row)
		{
			std::unique_ptr<Tile> col(new Tile(mTileset->getSprite(), sf::Vector2f(0.f, 0.f)));
		}
	}
}

	