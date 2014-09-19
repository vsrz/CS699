#include "EndState.h"
#include "Fileutils.h"
#include <iostream>
#include "GlobalConfig.h"
#include "Logger.h"

EndState::EndState(StateStack& stack, Context context)
	: State(stack, context)
{
	temp = false;

	mBackground.setFillColor(sf::Color(0, 0, 0, 128));
	mBackground.setPosition(0, 0);
	mBackground.setSize(sf::Vector2f(context.window->getSize().x, context.window->getSize().y));

	mThankYou.setString("Thank you for playing!");
	mThankYou.setCharacterSize(32);
	mThankYou.setFont(context.fonts->get(Fonts::Default));
	sf::FloatRect textRect = mThankYou.getLocalBounds();
	mThankYou.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); 
	mThankYou.setPosition(context.window->getSize().x * 0.5f, context.window->getSize().y * 0.5f);

	mScoreString.setFont(context.fonts->get(Fonts::Default));
	mScoreString.setString(context.score->getFinalScoreString());
	mScoreString.setCharacterSize(20);
	textRect = mScoreString.getLocalBounds();
	mScoreString.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	mScoreString.setPosition(context.window->getSize().x * 0.5f, context.window->getSize().y * 0.5f + 50.f);

	mPressToRestart.setFont(context.fonts->get(Fonts::Default));
	//mPressToRestart.setString("Please fill out the survey on the system next to you!");
	mPressToRestart.setCharacterSize(16);
	textRect = mPressToRestart.getLocalBounds();
	mPressToRestart.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	mPressToRestart.setPosition(context.window->getSize().x * 0.5f, context.window->getSize().y * 0.5f + 150.f);

	
}

void EndState::saveScore(std::string scoreString)
{
	Logger& l = Logger::get();
	Fileutils::writeFileToDisk(scoreString, GlobalConfig::get().SCORE_FILENAME);
	ScoreGenerator score = *getContext().score;
	GlobalConfig::logSettings();
	l.log("Game has ended");
	l.log("Served: " + toString(score.getServedCustomers()) + "/" + toString(score.getTotalCustomers()) + " Cash: " + toString(score.getRevenue()) + " Tips: " + toString(score.getTips()));
	l.write();
}

void EndState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackground);
	window.draw(mThankYou);
	window.draw(mScoreString);
	window.draw(mPressToRestart);

}

void EndState::setScore(ScoreGenerator score)
{
	mScore = score;
}

bool EndState::update(sf::Time dt)
{
	if (temp == false)
	{
		std::cout << mScore.getScoreString() << "\n";
		temp = true;
	}

	return true;
}

bool EndState::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
	{
		ScoreGenerator& scores = *getContext().score;
		saveScore(scores.getScoreString());
		scores.resetScores();
		requestStackPop();
		requestStackPush(States::Title);
	}
	return false;
}
