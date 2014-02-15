#include "World.h"
#include <iostream>
#include "Glob.h"

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mSceneGraph()
	, mSceneLayers()
	, mTextures()
	, mTilemap()
	, mWorldScale(2.f, 2.f)
{
	loadTextures();
	buildScene();


}

sf::Vector2f World::getWorldScale()
{
	return mWorldScale;
}

void World::update(sf::Time dt)
{
	mSceneGraph.update(dt);

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
	mTilemap.loadTilemap("res/Tilemap.tmx");
}

// Return a tile coordinate relative to a pixel coordinate on the screen
sf::Vector2i World::getTilePosition(sf::Vector2i windowPos)
{
	sf::Vector2i position;
	position.x = windowPos.x / 
		(mTilemap.getTileSize().x * mWorldScale.x);
	position.y = windowPos.y /
		(mTilemap.getTileSize().y * mWorldScale.y);

	return position;
}

// Return the pixel position given a tile coordinate
sf::Vector2f World::getPixelsFromTilePosition(const sf::Vector2i& tilePos)
{
	return sf::Vector2f(
		static_cast<float>(tilePos.x * mWorldScale.x * mTilemap.getTileSize().x),
		static_cast<float>(tilePos.y * mWorldScale.y * mTilemap.getTileSize().y)
		);
}

// Return the pixel position of a tile given the position of a pixel
sf::Vector2f World::getPixelPosition(const sf::Vector2i& pixelPos)
{
	sf::Vector2i p = getTilePosition(pixelPos);
	sf::Vector2f position(static_cast<float>(p.x), static_cast<float>(p.y));
		
	position.x = position.x * mWorldScale.x * mTilemap.getTileSize().x;
	position.y = position.y * mWorldScale.y * mTilemap.getTileSize().y;
	return position;
}

void World::handleEvent(const sf::Event& event)
{
	extern sf::String g_debugData;
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	sf::Vector2i mouseTilePosition = getTilePosition(mousePosition);
	if (event.type == sf::Event::MouseButtonPressed)
	{
#ifdef DEBUG
		// Update some debug tile stuff
		g_debugData = "Tile Num: " + toString(mTilemap.getTileNumber(mouseTilePosition.x, mouseTilePosition.y));
		g_debugData += "\nBlocking: " + toString(mTiles[mTilemap.getTileNumber(mouseTilePosition.x, mouseTilePosition.y)].isBlocking());
		g_debugData += "\nTile: " + toString(mouseTilePosition.x) + "," + toString(mouseTilePosition.y);
#endif
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mPlayer->setDestination(mousePosition);
		
		}
	}




}


void World::buildScene()
{
	std::unique_ptr<SpriteNode> tile;
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
			sf::Vector2f worldPos = mTilemap.getWorldPosition(x * mWorldScale.x ,y * mWorldScale.y);
			sf::Texture& texture = mTilemap.getTexture(x, y, "Floor");
			
			// Since Spritenode is stored as a single array, we need the position relative to
			// its X, Y coordinates--just like the tmx GID number
			int tilePos = x + y * mTilemap.getWorldSize().y;
			
			if (textureRect.left < 0) continue;

			tile = std::unique_ptr<SpriteNode>(new SpriteNode(texture, textureRect));
			tile->setPosition(worldPos);
			tile->setScale(mWorldScale);
			mSceneLayers[Floor]->attachChild(std::move(tile));
		}

	}

	/* Build the object tileset */
	for (int y = 0; y < mTilemap.getWorldSize().y; y++)
	{
		for (int x = 0; x < mTilemap.getWorldSize().x; x++)
		{
			sf::IntRect textureRect = mTilemap.getTextureRect(x, y, "Object");
			sf::Vector2f worldPos = mTilemap.getWorldPosition(x * mWorldScale.x ,y * mWorldScale.y);
			sf::Texture& texture = mTilemap.getTexture(x, y, "Object");
			
			// Since Spritenode is stored as a single array, we need the position relative to
			// its X, Y coordinates--just like the tmx GID number
			int tilePos = x + y * mTilemap.getWorldSize().y;
			
			// If there is no texture assigned to this tile, move on
			if (textureRect.left < 0) continue;

			tile = std::unique_ptr<SpriteNode>(new SpriteNode(texture, textureRect));
			tile->setPosition(worldPos);
			tile->setScale(mWorldScale);
			mSceneLayers[Object]->attachChild(std::move(tile));
			mTiles[mTilemap.getTileNumber(x,y)].setProperty(Tiles::Blocking);
		}

	}

	/* Build the object tileset */
	for (int y = 0; y < mTilemap.getWorldSize().y; y++)
	{
		for (int x = 0; x < mTilemap.getWorldSize().x; x++)
		{
			sf::IntRect textureRect = mTilemap.getTextureRect(x, y, "PassableObject");
			sf::Vector2f worldPos = mTilemap.getWorldPosition(x * mWorldScale.x ,y * mWorldScale.y);
			sf::Texture& texture = mTilemap.getTexture(x, y, "PassableObject");
			
			// Since Spritenode is stored as a single array, we need the position relative to
			// its X, Y coordinates--just like the tmx GID number
			int tilePos = x + y * mTilemap.getWorldSize().y;
			
			// If there is no texture assigned to this tile, move on
			if (textureRect.left < 0) continue;

			tile = std::unique_ptr<SpriteNode>(new SpriteNode(texture, textureRect));
			tile->setPosition(worldPos);
			tile->setScale(mWorldScale);
			mSceneLayers[PassableObject]->attachChild(std::move(tile));
		}

	}
	
	/* Add a test player to the screen */
	std::unique_ptr<Player> player(new Player(mTextures, this));
	mPlayer = player.get();
	mSceneLayers[Entity]->attachChild(std::move(player));

}


