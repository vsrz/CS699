#include "World.h"


World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mSceneGraph()
	, mSceneLayers()
	, mImages()
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

}

void World::loadTileset()
{
	sf::Vector2i tilesize;
	mTileset.setTileSize(sf::Vector2i(32, 32));

	for (auto& tile : mTileMap)
	{
		//std::unique_ptr<Tile> t = new Tile(
	}
}

	