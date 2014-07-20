#ifndef GUISTATE_H
#define GUISTATE_H

#pragma once


#include "State.h"
#include "StateStack.h"
#include <SFGUI/SFGUI.hpp>
#include "GlobalConfig.h"

class GuiState :
	public State
{
public:
	GuiState(StateStack& stack, Context context);
	void initalize();
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
	
private:	

	sfg::SFGUI mSfgui;
	
	// Window Object
	sfg::Window::Ptr mWindow;
	
	// Button Objects
	sfg::Button::Ptr mExitButton;
	sfg::Button::Ptr mCancelButton;

	// Text entry objects

	// Slider/scale
	sfg::Scale::Ptr mCutHairSlider;
	sfg::Scale::Ptr mWashSlider;
	sfg::Scale::Ptr mColorSlider;
	sfg::Scale::Ptr mCustSpeedMultSlider;

	// Text Label objects
	sfg::Label::Ptr mLabel;

	// Entry objects
	sfg::Entry::Ptr mCutTimeEntry;
	sfg::Entry::Ptr mColorTimeEntry;
	sfg::Entry::Ptr mWashTimeEntry;
	sfg::Entry::Ptr mCustSpeedMultEntry;

	// Desktop Object
	sfg::Desktop mDesktop;

	// Button click event handlers
	void onExitButtonClicked();
	void onCancelButtonClicked();
	void onCutHairTimeAdjust();
	void onColorTimeAdjust();
	void onWashTimeAdjust();
	void onCustSpeedMultAdjust();

	// Layout generators
	sfg::Table::Ptr getSliderSettings();
	sfg::Box::Ptr getSpeedMultiplierBox();


};

#endif
