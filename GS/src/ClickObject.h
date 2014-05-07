#ifndef CLICKOBJECT_H
#define CLICKOBJECT_H

#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Glob.h"

/* Defines a click animation */


class ClickObject
{
public:
	ClickObject(sf::Texture& redClick, sf::Texture& greenClick);
	void addClickEvent(TilePosition position);

	void update(sf::Time dt);
	void draw(sf::RenderWindow& window);

private:
	sf::Texture& mRedClick;
	sf::Texture& mGreenClick;

	sf::Time mDuration;
	
	struct Click
	{
		sf::Sprite sprite;
		float fade;
		sf::Time time;	
	};

	std::vector<Click> mClick;

};

#endif
