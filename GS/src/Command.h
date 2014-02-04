#ifndef COMMAND_H
#define COMMAND_H

#pragma once

#include "Category.h"
#include <SFML/System.hpp>
#include <functional>
#include <cassert>

class SceneNode;

struct Command
{
	Command();
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

template<typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=] (SceneNode& node, sf::Time dt)
	{
		// check for safe cast
		assert(dynamic_cast<GameObject*> (&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&> (node), dt);
	};
}

#endif

