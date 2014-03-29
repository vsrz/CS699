#ifndef SCENENODE_H
#define SCENENODE_H
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>
#include "Command.h"
#include "Category.h"

class SceneNode : 
	public sf::Transformable, 
	public sf::Drawable, 
	private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	
	SceneNode(void);
	
	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);
	void update(sf::Time dt);
	void sortChildren();
	
	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

	virtual unsigned int getCategory() const;
	void onCommand(const Command& command, sf::Time dt);


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt);
	virtual float getZPosition();
	void updateChildren(sf::Time dt);

	std::vector<Ptr> mChildren;
	SceneNode*	mParent;

};

#endif

