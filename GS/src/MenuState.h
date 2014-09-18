#pragma once
#include "State.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class MenuState :
	public State
{
public:
	MenuState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	
	void updateOptionText();
private:
	enum OptionNames
	{
		Play,
		Exit,
	};

	bool isInRect(MousePosition pos, sf::Rect<float> rect);

	sf::Text mBuildInfo;
	sf::Sprite mBackgroundSprite0;
	sf::Sprite mBackgroundSprite1;
	sf::Sprite mBackgroundSprite2;
	sf::Sprite mStartButton;
	sf::Sprite mExitButton;
	sf::Texture& mStartButtonTexture;
	sf::Texture& mExitButtonTexture;

	std::vector<sf::Text> mOptions;
	std::size_t mOptionIndex;

};

