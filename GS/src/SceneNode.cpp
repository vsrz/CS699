#include "SceneNode.h"
#include <iostream>

/* Public Methods */
SceneNode::SceneNode(void)
{
	mParent = nullptr;
}

void SceneNode::attachChild(Ptr child)
{
	// attach this node to the current parent node
	child->mParent = this;

	// uses move to avoid the copy constructor?
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	// Search for the specified node in the container
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&node] (Ptr& p) -> bool { return p.get() == &node; });
	assert(found != mChildren.end());

	/* move the found node out of the container into result */
	Ptr result = std::move(*found);
	
	// set the parent node to point to nullptr
	result->mParent = nullptr;

	// erase the empty element from the Children container
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	// Update all the elements in this node
	updateCurrent(dt);
	updateChildren(dt);

}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();

}

sf::Transform SceneNode::getWorldTransform() const
{
	// The identity transform (basically, the null transform)
	sf::Transform transform = sf::Transform::Identity;

	// Cycle through each parent node until you reach the root node, combining
	// its transform 
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		transform = node->getTransform() * transform;
	}

	// Return the world position
	return transform;

}

// Returns the category of the game object in this scene node
// Override this for each game entity
unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}

// Run command through the appropriate child nodes
void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category & getCategory())
	{
		command.action(*this, dt);
	}

	for (Ptr& child : mChildren)
	{
		child->onCommand(command, dt);
	}
}

/* Private Methods */
void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	extern bool g_collisionOverlay;
	
	// the absolute transform of the current node (where the scene node is placed)
	states.transform *= getTransform();

	// Draw the derived object
	drawCurrent(target, states);

	// Draw all the child nodes using range based for C++11 syntax
	for (const Ptr& child : mChildren)
	{
		// dereference the iterator and call draw on its object
		child->draw(target, states);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{

}

void SceneNode::updateCurrent(sf::Time dt)
{

}

void SceneNode::updateChildren(sf::Time dt)
{
	// Loop through each child and call update() on it
	for (Ptr& child : mChildren)
	{
		child->update(dt);
	}
}




