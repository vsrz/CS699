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
	std::unique_ptr<Tileset> mTileset(new Tileset(mTextures.get(Textures::TestTileset)));
}

void World::loadTileset()
{

	for (auto& row : mTileMap)
	{
		std::cout << "Out" << std::endl;
	}
}

	