
#include "Tests.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>


void focusTest(sf::Event event)
{
	/* Focus */
	if (event.type == sf::Event::GainedFocus)
	{
		std::cout << "UnPaused" << std::endl;
	}

	else if (event.type == sf::Event::LostFocus)
	{
		std::cout << "Paused" << std::endl;
	}

}

void tileSetTest(sf::RenderWindow& window)
{
	sf::Texture texture;
	sf::Sprite sprite;
	
	texture.loadFromFile("res/Tileset.png");
	texture.setRepeated(true);
	sprite.setTexture(texture);
	
	window.draw(sprite);

	
}

void drawBox(sf::RenderWindow& window, sf::Vector2i pos)
{
	sf::RectangleShape rect(sf::Vector2f(33.f, 33.f));
	rect.setPosition(32.f * pos.x, 32.f * pos.y);
	//rect.setOrigin(32.f * 0.5, 32.f * 0.5);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(1.f);
	window.draw(rect);
	

}



void Tests::run()
{
	sf::RenderWindow mWindow(sf::VideoMode(1280, 720), "Test Window", sf::Style::Close);
	sf::Event event;
	sf::Vector2i pos(0,0);

	while (mWindow.isOpen())
	{
		while (mWindow.pollEvent(event))
		{
			mWindow.clear();
			tileSetTest(mWindow);
			drawBox(mWindow, pos);

			if (event.type == sf::Event::Closed)
			{
				mWindow.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					pos.y -= 1;
					
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					pos.x -= 1;

				}
				else if (event.key.code == sf::Keyboard::S)
				{
					pos.y += 1;
				}
				else if (event.key.code == sf::Keyboard::D)
				{
					pos.x += 1;

				}
			}
			mWindow.display();			
		}
	}
}
