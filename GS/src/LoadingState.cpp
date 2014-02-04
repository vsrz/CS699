
#include "LoadingState.h"
#include "ResourceHolder.h"
#include "Glob.h"

LoadingState::LoadingState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::RenderWindow& window = *getContext().window;	
	sf::Font& font = context.fonts->get(Fonts::Default);

	// Set the loading text and center it
	mLoadingText.setFont(font);
	mLoadingText.setString("Loading Resources");
	centerOrigin(mLoadingText);
	mLoadingText.setPosition(window.getSize().x * 0.5,
		window.getSize().y / 2u + 50);

	// Initialize the progress bar background
	mProgressBarBackground.setFillColor(sf::Color::White);
	mProgressBarBackground.setSize(sf::Vector2f(window.getSize().x * 0.4f, 10));
	mProgressBarBackground.setPosition(sf::Vector2f(window.getSize().x * 0.5f - mProgressBarBackground.getSize().x * 0.5f
		, mLoadingText.getPosition().y + 40));

	// Initialize the progress bar itself
	mProgressBar.setFillColor(sf::Color::Green);
	mProgressBar.setSize(sf::Vector2f(200,10));
	mProgressBar.setPosition(mProgressBarBackground.getPosition().x,
		mProgressBarBackground.getPosition().y);
	
	setCompletion(0.f);

	mLoadingTask.execute();

}

bool LoadingState::update(sf::Time dt)
{
	if (mLoadingTask.isFinished())
	{
		requestStackPop();
		requestStackPush(States::Game);
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

	// Fill the progress bar based on the percentage amount
	mProgressBar.setSize(sf::Vector2f(mProgressBarBackground.getSize().x
		* percent, mProgressBar.getSize().y));

	return true;
}

