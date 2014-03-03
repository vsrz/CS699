
#include "Tests.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>
#include <array>
#include "TinyXML2/tinyxml2.h"

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
	
	texture.loadFromFile("res/TestTileset.png");
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

void arrayTest()
{
	std::array<std::array<int*, 2>, 2> ints;
	for(auto& i : ints)
	{
		for (auto& i2 : i)
		{
			i2 = new int(8);

		}
	}
	std::cout << *ints[0][0] << std::endl;

	std::shared_ptr<int> z;
	{
		std::shared_ptr<int> i(new int(8));
		z = i;
	}
	std::cout << z << std::endl;
}


void readAttribute(tinyxml2::XMLElement* element, const char* attribute)
{

}

void tinyXMLTest()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* mapElement;
	int mMapWidth;
	int mMapHeight;
	doc.LoadFile("res/TileLoader.tmx");
	sf::String s =	doc.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile")->Attribute("gid");
	std::cout << s.toAnsiString() << std::endl;

	// Read map element
	mapElement = doc.FirstChildElement("map")->ToElement();
	
	if (!mapElement)
	{
		throw std::runtime_error("Unable to load map element from XMLDocument");
	}
	mMapWidth = mapElement->IntAttribute("width");
	mMapHeight = mapElement->IntAttribute("height");

	std::cout << "Map Width: " << mMapWidth << std::endl << "Map Height: " << mMapHeight << std::endl;
	
	int child = 0;
	tinyxml2::XMLElement* iElement = mapElement->FirstChildElement("layer")->ToElement();
	for (iElement; iElement; iElement = iElement->NextSiblingElement())
	{
		std::cout << iElement->Attribute("name") << std::endl;
	} 
}

enum D
{
	None	= 0,
	South	= 1 << 1,
	North	= 1 << 2,
	West	= 1 << 3,
	East	= 1 << 4,

};


void bitw()
{
	std::size_t dir;
	dir = D::North;
	dir |= D::South;
	std::cout << (D::North & dir) << " " << dir;	
}


void ptrtest()
{
	std::unique_ptr<int> i = std::unique_ptr<int>(new int(9));

}

void configtest()
{
	//std::string s = GlobalConfig::get().getValue<std::string>(std::string("This"));
	std::string s;
	std::cout << std::endl << s;
	
	std::cout << std::endl << "Press any key...";
	char ch = std::cin.get();


}

void Tests::run()
{
	configtest();

	sf::RenderWindow mWindow(sf::VideoMode(1280, 720), "Test Window", sf::Style::Close);
	sf::Event event;
	sf::Vector2i pos(0,0);

	//tinyXMLTest();
	//return;
	
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
