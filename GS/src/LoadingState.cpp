
#include "LoadingState.h"
#include "ResourceManager.h"
#include "Glob.h"
#include "Logger.h"

LoadingState::LoadingState(StateStack& stack, Context context)
	: State(stack, context)
	, mLoadingTask(context)
{
	sf::RenderWindow& window = *getContext().window;	
	sf::Font& font = context.fonts->get(Fonts::Default);
	extern bool g_GameResourcesLoaded;

	// Set the loading text and center it
	mLoadingText.setFont(font);
	mLoadingText.setString("Loading Resources");
	centerOrigin(mLoadingText);
	mLoadingText.setPosition(window.getSize().x * 0.5f,
		window.getSize().y * 0.5f + 50.f);

	// Initialize the progress bar background
	mProgressBarBackground.setFillColor(sf::Color::White);
	mProgressBarBackground.setSize(sf::Vector2f(window.getSize().x * 0.4f, 10));
	mProgressBarBackground.setPosition(sf::Vector2f(window.getSize().x * 0.5f - mProgressBarBackground.getSize().x * 0.5f
		, mLoadingText.getPosition().y + 40.f));

	// Initialize the progress bar itself
	mProgressBar.setFillColor(sf::Color::Blue);
	mMaxProgressSize = mProgressBarBackground.getSize().x;
	mProgressBar.setSize(sf::Vector2f(0, 10));
	mProgressBar.setPosition(mProgressBarBackground.getPosition().x,
		mProgressBarBackground.getPosition().y);
	
	setCompletion(20.f);

	if (g_GameResourcesLoaded == false)
		mLoadingTask.execute();

}

bool LoadingState::update(sf::Time dt)
{
	extern bool g_GameResourcesLoaded;

	if (mLoadingTask.isFinished() || g_GameResourcesLoaded == true)
	{
		requestStackPop();
		requestStackPush(States::Game);
		g_GameResourcesLoaded = true;
	}
	else
	{
		setCompletion(mLoadingTask.getCompletion());
	}

	return true;
}

void LoadingState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(mLoadingText);
	window.draw(mProgressBarBackground);
	window.draw(mProgressBar);

}


bool LoadingState::handleEvent(const sf::Event& event)
{
	return true;
}

bool LoadingState::setCompletion(float percent)
{
	// Do not allow the progress bar to exceed 100%
	if (percent > 1.f) percent = 1.f;

	// Fill the progress bar based on the percentage 
	mProgressBar.setSize(sf::Vector2f(mMaxProgressSize* percent, mProgressBar.getSize().y));

	return true;
}

