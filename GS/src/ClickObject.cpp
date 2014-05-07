#include "ClickObject.h"
#include "Glob.h"
#include <iostream>

ClickObject::ClickObject(sf::Texture& redClick, sf::Texture& greenClick)
	: mRedClick(redClick)
	, mGreenClick(greenClick)
{
	
	mDuration = sf::seconds(0.6f);
}

// createa a new click event
void ClickObject::addClickEvent(sf::Vector2f position)
{
	Click click;
	float scale = Config::WORLD_SCALE;
	click.sprite.setPosition(position);
	click.sprite.setScale(scale, scale);
	click.sprite.setTexture(mRedClick);

	// Check for special cases of click, otherwise use the red button
	for (auto itr = Config::Chairs::SEATING_POSITION.begin();
		itr != Config::Chairs::SEATING_POSITION.end();
		++itr)
	{
		if (*itr == toTilePosition(position))
		{
			click.sprite.setTexture(mGreenClick);
		}
	}
	for (auto itr = Config::RegisterQueue::REGISTER_POSITION.begin();
		itr != Config::RegisterQueue::REGISTER_POSITION.end();
		++itr)
	{
		if (*itr == toTilePosition(position))
		{
			click.sprite.setTexture(mGreenClick);
		}
	}


	click.time = mDuration;
	click.fade = 1.f;
	mClick.push_back(click);
}

void ClickObject::update(sf::Time dt)
{
	for (auto iter = mClick.begin(); iter != mClick.end(); ++iter)
	{
		if (iter->time - dt > sf::Time::Zero)
		{
			iter->time -= dt;
			iter->fade = 1 * (static_cast<float>(iter->time.asMilliseconds()) 
				/ static_cast<float>(mDuration.asMilliseconds()));
		} else iter->fade = 0;
		iter->sprite.setColor(sf::Color(255,255,255,static_cast<int>(255 * iter->fade)));
	} 
}

void ClickObject::draw(sf::RenderWindow& window)
{
	for (auto iter = mClick.begin(); iter != mClick.end(); ++iter)
	{
		window.draw(iter->sprite);
	}

}

