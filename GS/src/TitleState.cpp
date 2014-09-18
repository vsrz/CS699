#include "TitleState.h"
#include "ResourceManager.h"
#include "Glob.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, mShowText(true)
	, mTextEffectTime(sf::Time::Zero)
{
	// Construct build ID
	mBuildInfo.setFont(context.fonts->get(Fonts::Default));
	mBuildInfo.setCharacterSize(12);
	mBuildInfo.setPosition(sf::Vector2f(1160.f, 750.f));
	mBuildInfo.setString(Config::RELEASE_STRING);

	mText.setFont(context.fonts->get(Fonts::Default));
	mText.setString("Press any key to start");
	mText.setCharacterSize(36);
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	sf::Texture& texture0 = getContext().textures->get(Textures::TitleScreen0);
	sf::Texture& texture1 = getContext().textures->get(Textures::TitleScreen1);
	sf::Texture& texture2 = getContext().textures->get(Textures::TitleScreen2);
	
	mBackgroundSprite0 = sf::Sprite(texture0);
	mBackgroundSprite0.setPosition(sf::Vector2f(0.f, 0.f));
	mBackgroundSprite1 = sf::Sprite(texture1);
	mBackgroundSprite1.setPosition(sf::Vector2f(426.f, 0.f));
	mBackgroundSprite2 = sf::Sprite(texture2);
	mBackgroundSprite2.setPosition(sf::Vector2f(852.f, 0.f));

	window.draw(mBackgroundSprite0);
	window.draw(mBackgroundSprite1);
	window.draw(mBackgroundSprite2);

	window.draw(mBuildInfo);
	if (mShowText)
	{
		//window.draw(mText);
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
	/* Lazy way to completely abort this state -- we don't need it */
	requestStackPop();
	requestStackPush(States::Menu);

	// If the any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}

