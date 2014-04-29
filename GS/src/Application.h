#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "World.h"
#include "Glob.h"
#include "StateStack.h"
#include "ScoreGenerator.h"


class Application
	: private sf::NonCopyable
{
public:
	Application(void);	
	~Application(void);

	void run();

private:
	void processEvents();
	void update(sf::Time);
	void render();
	void processInput();

	void registerStates();
	
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;	

	TextureManager mTextures;
	FontManager mFonts;
	StateStack mStateStack;
	ScoreGenerator mScore;

};

#endif
