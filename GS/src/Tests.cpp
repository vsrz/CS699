
#include "Tests.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void Tests::run()
{
	sf::Window mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close);
	sf::Event event;

	while (mWindow.isOpen())
	{
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::GainedFocus)
				std::cout << "UnPaused" << std::endl;
			else if (event.type == sf::Event::LostFocus)
				std::cout << "Paused" << std::endl;

		}
	}
}
