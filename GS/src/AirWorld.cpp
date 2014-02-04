#include "World.h"
#include <iostream>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
	, mSpawnPosition(
		mWorldView.getSize().x / 2.f, 
		mWorldBounds.height - mWorldView.getSize().y -100
		)
	, mScrollSpeed(0.f)
	, mPlayerAircraft(nullptr)
	, mSceneLayers()
	, mSceneGraph()
	 	  
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);

}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}
void World::update(sf::Time dt)
{
	// Move the background texture
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	
	mPlayerAircraft->setVelocity(0.f, 0.f);

	// Handle commands for this tick
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}
	adaptPlayerVelocity();
	mSceneGraph.update(dt);
	adaptPlayerPosition();
}

// Provide access to the command queue to outside entities
CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	mTextures.load(Textures::Eagle, "res/Eagle.png");
	mTextures.load(Textures::Raptor, "res/Raptor.png");
	mTextures.load(Textures::Desert, "res/Desert.png");
	mTextures.load(Textures::Tileset, "res/Tileset.png");

}

void World::buildScene()
{
	/**
	 * Initialize the scene layer by iterating through the
	 * layer nodes then attaching the new node to the scene graph
	 **/
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		
		// Return the raw pointer to this stored object
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));

	}

	// Configure the desert texture to repeat itself
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add the airplanes to the scene
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// Give the leader two escorts
	/*std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
	*/


}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// If the player is moving diagonally, adapt it so it's consistent
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

	// Scrolling velocity
	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}

void World::adaptPlayerPosition()
{
	// Make sure the player stays within the bounds of the screen
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	
	mPlayerAircraft->setPosition(position);
}