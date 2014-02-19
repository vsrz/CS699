#include "World.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "Glob.h"

#define WORLD_SCALE 2
#define WORLD_WIDTH 20
#define WORLD_HEIGHT 12
#define TILE_HEIGHT 32
#define TILE_WIDTH 32


World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mSceneGraph()
	, mSceneLayers()
	, mTextures()
	, mTileLoader()
	, mWorldScale(2.f, 2.f)
	, mTilemap(WORLD_WIDTH, WORLD_HEIGHT, TILE_WIDTH, TILE_HEIGHT, WORLD_SCALE)
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
	mTileLoader.loadFromFile("res/Tilemap.tmx");
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
		g_debugData["Occupied"] = toString(mTilemap.isTileOccupied(mousePosition));
		g_debugData["Tile"] = toString(mouseTilePosition.x) + "," + toString(mouseTilePosition.y);
#endif
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mPlayer->setDestination(mousePosition);
#ifdef DEBUG
			g_debugData["Destination:"] = toString(mousePosition.x) + "," + toString(mousePosition.y);
#endif
		}
	}
	else if (event.type == sf::Event::KeyPressed && 
		event.key.code == sf::Keyboard::F4)
	{
		std::unique_ptr<SpriteNode> tile;

	/* Debug layer */
#ifdef DEBUG
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
#endif
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
	for (int y = 0; y < mTileLoader.getWorldSize().y; y++)
	{
		for (int x = 0; x < mTileLoader.getWorldSize().x; x++)
		{
			sf::IntRect textureRect = mTileLoader.getTextureRect(x, y, "Floor");
			sf::Vector2f worldPos = mTileLoader.getWorldPosition(x * mWorldScale.x ,y * mWorldScale.y);
			sf::Texture& texture = mTileLoader.getTexture(x, y, "Floor");
			
			// Since Spritenode is stored as a single array, we need the position relative to
			// its X, Y coordinates--just like the tmx GID number
			int tilePos = x + y * mTileLoader.getWorldSize().y;
			
			if (textureRect.left < 0) continue;

			tile = std::unique_ptr<SpriteNode>(new SpriteNode(texture, textureRect));
			tile->setPosition(worldPos);
			tile->setScale(mWorldScale);
			mSceneLayers[Floor]->attachChild(std::move(tile));
		}

	}

	/* Build the object tileset */
	for (int y = 0; y < mTileLoader.getWorldSize().y; y++)
	{
		for (int x = 0; x < mTileLoader.getWorldSize().x; x++)
		{
			sf::IntRect textureRect = mTileLoader.getTextureRect(x, y, "Object");
			sf::Vector2f worldPos = mTileLoader.getWorldPosition(x * mWorldScale.x ,y * mWorldScale.y);
			sf::Texture& texture = mTileLoader.getTexture(x, y, "Object");
			
			// Since Spritenode is stored as a single array, we need the position relative to
			// its X, Y coordinates--just like the tmx GID number
			int tilePos = x + y * mTileLoader.getWorldSize().y;
			
			// If there is no texture assigned to this tile, move on
			if (textureRect.left < 0) continue;

			tile = std::unique_ptr<SpriteNode>(new SpriteNode(texture, textureRect));
			tile->setPosition(worldPos);
			tile->setScale(mWorldScale);
			mSceneLayers[Object]->attachChild(std::move(tile));
			mTilemap.setTileProperty(x,y, Tiles::Property::Occupied);
		}

	}

	/* Build the object tileset */
	for (int y = 0; y < mTileLoader.getWorldSize().y; y++)
	{
		for (int x = 0; x < mTileLoader.getWorldSize().x; x++)
		{
			sf::IntRect textureRect = mTileLoader.getTextureRect(x, y, "PassableObject");
			sf::Vector2f worldPos = mTileLoader.getWorldPosition(x * mWorldScale.x ,y * mWorldScale.y);
			sf::Texture& texture = mTileLoader.getTexture(x, y, "PassableObject");
			
			// Since Spritenode is stored as a single array, we need the position relative to
			// its X, Y coordinates--just like the tmx GID number
			int tilePos = x + y * mTileLoader.getWorldSize().y;
			
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


