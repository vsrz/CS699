#include "ClickObject.h"
#include <iostream>

ClickObject::ClickObject(sf::Texture& texture)
	: mTexture(texture)
{
	
	mDuration = sf::seconds(0.8f);
}

// createa a new click event
void ClickObject::addClickEvent(sf::Vector2f position)
{
	Click click;
	float scale = Config::WORLD_SCALE;
	click.sprite.setPosition(position);
	click.sprite.setScale(scale, scale);
	click.sprite.setTexture(mTexture);
	click.time = mDuration;
	click.fade = 255;
	mClick.push_back(click);
}

void ClickObject::update(sf::Time dt)
{
	for (auto iter = mClick.begin(); iter != mClick.end(); ++iter)
	{
		if (iter->time - dt > sf::Time::Zero)
		{
			iter->time -= dt;
			iter->fade = 255 * 
				(iter->time.asMilliseconds() 
				/ mDuration.asMilliseconds());
		} else iter->fade = 0;
		iter->sprite.setColor(sf::Color(255,255,255,iter->fade));
	} 
}

void ClickObject::draw(sf::RenderWindow& window)
{
	for (auto iter = mClick.begin(); iter != mClick.end(); ++iter)
	{
		window.draw(iter->sprite);
	}

}

