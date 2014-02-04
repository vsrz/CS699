#include "TitleState.h"
#include "ResourceManager.h"
#include "Glob.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, mShowText(true)
	, mTextEffectTime(sf::Time::Zero)
{
	mText.setFont(context.fonts->get(Fonts::Default));
	mText.setString("Press any key to start");
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	sf::Texture& texture = getContext().textures->get(Textures::TitleScreen);
	texture.setRepeated(true);
	sf::IntRect rect(0, 0, getContext().window->getSize().x, getContext().window->getSize().y);

	mBackgroundSprite = sf::Sprite(texture, rect);
	
	window.draw(mBackgroundSprite);

	if (mShowText)
	{
		window.draw(mText);
	}
}

bool TitleState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	// set the text to blink every 0.5f
	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	// If the any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}

