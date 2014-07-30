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

	// Slider/scale
	sfg::Scale::Ptr mCutHairSlider;
	sfg::Scale::Ptr mWashSlider;
	sfg::Scale::Ptr mColorSlider;
	sfg::Scale::Ptr mCustSpeedMultSlider;
	sfg::Scale::Ptr mRegisterUseTimeScale;
	sfg::Scale::Ptr mStateTickMultScale;
	sfg::Scale::Ptr mPatiencePenaltyMultScale;
	sfg::Scale::Ptr mCustReleaseTickScale;

	// Text Label objects
	sfg::Label::Ptr mLabel;

	// Entry objects
	sfg::Entry::Ptr mCutTimeEntry;
	sfg::Entry::Ptr mColorTimeEntry;
	sfg::Entry::Ptr mWashTimeEntry;
	sfg::Entry::Ptr mCustSpeedMultEntry;
	sfg::Entry::Ptr mRegisterUseEntry;
	sfg::Entry::Ptr mStateTickMultEntry;
	sfg::Entry::Ptr mPatiencePenaltyMultEntry;
	sfg::Entry::Ptr mCustReleaseTickEntry;
	sfg::Entry::Ptr mAllocationPointsEntry;

	// Desktop Object
	sfg::Desktop mDesktop;

	// Button click event handlers
	void onExitButtonClicked();
	void onCancelButtonClicked();
	void onCutHairTimeAdjust();
	void onColorTimeAdjust();
	void onWashTimeAdjust();
	void onRegUseTimeAdjust();
	void onCustSpeedMultAdjust();
	void onStateTickMultAdjust();
	void onPatiencePenaltyMultAdjust();
	void onCustReleaseTickAdjust();

	// Remaining allocation points
	bool checkAllocation(float cost);
	float getRemainingAllocationPoints();
	void setRemainingAllocationPoints(float points);
	
	// Layout generators
	sfg::Table::Ptr getSliderSettings();
	sfg::Box::Ptr getSpeedMultiplierBox();

	

	void saveSettings();
};

#endif
