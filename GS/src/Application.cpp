#include "Application.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "DebugScreenState.h"
#include "LoadingState.h"
#include "EndState.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

#ifdef DEBUG
Application::Application(void) 
	: mWindow(sf::VideoMode(1280, 768), "GS", sf::Style::Close)
	, mFonts()
	, mTextures()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mScore))
#else
Application::Application(void) 
	: mWindow(sf::VideoMode(1280, 768), "Gracie's Salon", sf::Style::Close)
	, mFonts()
	, mTextures()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mScore))
#endif
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);
	mFonts.load(Fonts::Default, "res/Sansation.ttf");
	mFonts.load(Fonts::Bit, "res/8b.ttf");

	mTextures.load(Textures::TitleScreen0, "res/title_0.png");
	mTextures.load(Textures::TitleScreen1, "res/title_1.png");
	mTextures.load(Textures::TitleScreen2, "res/title_2.png");

	registerStates();
#ifdef DEBUG
	mStateStack.pushState(States::Loading);
#endif

#ifdef RELEASE
	mStateStack.pushState(States::Title);
#endif

}


Application::~Application(void)
{

}

void Application::run(void)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{	
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);

			if (mStateStack.isEmpty())
			{
				mWindow.close();
			}
		}
		render();

	}
}

void Application::processInput()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}	

void Application::update(sf::Time elapsedTime)
{
	mStateStack.update(elapsedTime);
}

void Application::render(void)
{
	mWindow.clear();
	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<DebugScreenState>(States::Debug);
	mStateStack.registerState<LoadingState>(States::Loading);
	mStateStack.registerState<EndState>(States::End);
}

