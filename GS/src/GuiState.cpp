#include "GuiState.h"
#include "GlobalConfig.h"
#include "Glob.h"
#include <string>
#include "Logger.h"

GuiState::GuiState(StateStack& stack, Context context)
: State(stack, context)
{
	initalize();
	
}

void GuiState::initalize()
{
	GlobalConfig& g_cfg = GlobalConfig::get();

	mWindow = sfg::Window::Create();
	mWindow->SetTitle("Game Timer Control");
	mWindow->SetPosition(sf::Vector2f(1280.f / 4, 720.f / 5));
	mDesktop.Add(mWindow);
	
	// Generate the Bottom Box that holds the buttons
	auto button_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 0.5f);
	button_box->SetSpacing(5.f);
	mExitButton = sfg::Button::Create("Save");
	mExitButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GuiState::onExitButtonClicked, this));
	
	mCancelButton = sfg::Button::Create("Cancel");
	mCancelButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GuiState::onCancelButtonClicked, this));

	mResetButton = sfg::Button::Create("Revert");
	mResetButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GuiState::onResetButtonClicked, this));
	
	button_box->Pack(mResetButton);
	button_box->Pack(mCancelButton);
	button_box->Pack(mExitButton);

	mAllocationPointsEntry = sfg::Entry::Create(std::to_string(g_cfg.ALLOCATION_POINTS));

	// Add components to window
	auto content_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 15.f);
	content_box->Pack(getSliderSettings());
	content_box->Pack(button_box);
	mWindow->Add(content_box);

}

void GuiState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.resetGLStates();
	mSfgui.Display(window);
}

bool GuiState::update(sf::Time dt)
{
	mWindow->Update(dt.asSeconds());
	return false;
}

bool GuiState::handleEvent(const sf::Event& event)
{
	mWindow->HandleEvent(event);
	return false;
}

void GuiState::saveSettings()
{
	GlobalConfig& config = GlobalConfig::get();
	
	config.CUT_USE_TIME = mCutHairSlider->GetValue();
	config.WASH_USE_TIME = mWashSlider->GetValue();
	config.COLOR_USE_TIME = mColorSlider->GetValue();
	config.CUSTOMER_SPEED_MULTIPLIER = mCustSpeedMultSlider->GetValue();
	config.REGISTER_USE_TIME = mRegisterUseTimeScale->GetValue();
	config.CUSTOMER_RELEASE_INTERVAL = mCustReleaseTickScale->GetValue();
	config.STATE_CHANGE_COOLDOWN_MULTIPLIER = mStateTickMultScale->GetValue();
	config.PATIENCE_PENALTY_MULTIPLIER = mPatiencePenaltyMultScale->GetValue();
	config.ALLOCATION_POINTS = getRemainingAllocationPoints();

	config.logSettings();
}

// Get the remaining allocation points
float GuiState::getRemainingAllocationPoints()
{
	std::cout << std::stof(mAllocationPointsEntry->GetText().toAnsiString()) << std::endl;
	return std::stof(mAllocationPointsEntry->GetText().toAnsiString());

}

// Sets the entry box text truncating the string if possible
void GuiState::setEntryText(sfg::Entry* entry, float value, int precision)
{
	float val = rndTenth(value);
	std::ostringstream ss;
	ss.precision(precision);
	ss << val;
	entry->SetText(ss.str());
}

// Set the allocation points
void GuiState::setRemainingAllocationPoints(float points)
{
	float val = rndTenth(points);
	std::ostringstream ss;
	ss.precision(3);
	ss << val;
	mAllocationPointsEntry->SetText(ss.str());

}

// Check the allocation and remove points
bool GuiState::checkAllocation(float cost)
{
	float points = getRemainingAllocationPoints();
	cost = rndTenth(cost);
	if (cost > 0 && cost > points || points - cost >= 1000)
	{
		return false;
	}
	setRemainingAllocationPoints(points - cost);
	return true;

}

void GuiState::onExitButtonClicked()
{
	saveSettings();
	requestStackPop();
	
}

void GuiState::onCancelButtonClicked()
{
	requestStackPop();
}

void GuiState::onResetButtonClicked()
{
	GlobalConfig::get().reset();
	requestStackPop();
	requestStackPush(States::Gui);
}

void GuiState::onCutHairTimeAdjust()
{
	float cost = 100.f;
	float val = rndTenth(mCutHairSlider->GetValue());
	float chg = rndTenth(mCutHairSlider->GetAdjustment()->GetValue()) - std::stof(mCutTimeEntry->GetText().toAnsiString());

	if (checkAllocation(cost * chg * -1))
	{
		setEntryText(mCutTimeEntry.get(), val);
	}
	else
	{
		setEntryText(mCutTimeEntry.get(), val);
		mCutHairSlider->SetValue(val - chg);
	}

}

void GuiState::onWashTimeAdjust()
{
	float cost = 100.f;
	float val = rndTenth(mWashSlider->GetValue());
	float chg = rndTenth(mWashSlider->GetAdjustment()->GetValue()) - std::stof(mWashTimeEntry->GetText().toAnsiString());

	if (checkAllocation(cost * chg * -1))
	{
		setEntryText(mWashTimeEntry.get(), val);
	}
	else
	{
		setEntryText(mWashTimeEntry.get(), val - chg);
		mWashSlider->SetValue(val - chg);
	}
}

void GuiState::onCustSpeedMultAdjust()
{
	float cost = 100.f;
	float val = rndTenth(mCustSpeedMultSlider->GetValue());
	float chg = rndTenth(mCustSpeedMultSlider->GetAdjustment()->GetValue()) - std::stof(mCustSpeedMultEntry->GetText().toAnsiString());

	if (checkAllocation(cost * chg))
	{
		setEntryText(mCustSpeedMultEntry.get(), val);
	}
	else
	{
		setEntryText(mCustSpeedMultEntry.get(), val);
		mCustSpeedMultSlider->SetValue(val - chg);
	}

}

void GuiState::onColorTimeAdjust()
{
	float cost = 100.f;
	float val = rndTenth(mColorSlider->GetValue());
	float chg = rndTenth(mColorSlider->GetAdjustment()->GetValue()) - std::stof(mColorTimeEntry->GetText().toAnsiString());

	if (checkAllocation(cost * chg * -1))
	{
		setEntryText(mColorTimeEntry.get(), val);
	}
	else
	{
		setEntryText(mColorTimeEntry.get(), val - chg);
		mColorSlider->SetValue(val - chg);
	}

}

void GuiState::onRegUseTimeAdjust()
{
	float cost = 100.f;
	float val = rndTenth(mRegisterUseTimeScale->GetValue());
	float chg = rndTenth(mRegisterUseTimeScale->GetAdjustment()->GetValue()) - std::stof(mRegisterUseEntry->GetText().toAnsiString());

	if (checkAllocation(cost * chg * -1))
	{
		setEntryText(mRegisterUseEntry.get(), val);

	}
	else
	{
		setEntryText(mRegisterUseEntry.get(), val - chg);
		mRegisterUseTimeScale->SetValue(val - chg);
	}
}

void GuiState::onStateTickMultAdjust()
{
	float cost = 100.f;
	float val = rndTenth(mStateTickMultScale->GetValue());
	float chg = rndTenth(mStateTickMultScale->GetAdjustment()->GetValue()) - std::stof(mStateTickMultEntry->GetText().toAnsiString());

	if (checkAllocation(cost * chg))
	{
		setEntryText(mStateTickMultEntry.get(), val);
	}
	else
	{
		setEntryText(mStateTickMultEntry.get(), val - chg);
		mStateTickMultScale->SetValue(val - chg);
	}
}

void GuiState::onPatiencePenaltyMultAdjust()
{
	float cost = 100.f;
	float val = rndTenth(mPatiencePenaltyMultScale->GetValue());
	float chg = rndTenth(mPatiencePenaltyMultScale->GetAdjustment()->GetValue()) - std::stof(mPatiencePenaltyMultEntry->GetText().toAnsiString());

	if (checkAllocation(-1 * cost * chg))
	{
		setEntryText(mPatiencePenaltyMultEntry.get(), val);
	}
	else
	{
		setEntryText(mPatiencePenaltyMultEntry.get(), val);
		mPatiencePenaltyMultScale->SetValue(val - chg);
	}
}

void GuiState::onCustReleaseTickAdjust()
{
	float cost = 10.f;
	float val = rndTenth(mCustReleaseTickScale->GetValue());
	float chg = rndTenth(mCustReleaseTickScale->GetAdjustment()->GetValue()) - std::stof(mCustReleaseTickEntry->GetText().toAnsiString());

	if (checkAllocation(cost * chg))
	{
		setEntryText(mCustReleaseTickEntry.get(), val);
	}
	else
	{
		setEntryText(mCustReleaseTickEntry.get(), val - chg);
		mCustReleaseTickScale->SetValue(val - chg);
	}
}

sfg::Table::Ptr GuiState::getSliderSettings()
{
	GlobalConfig& g_cfg = GlobalConfig::get();	

	sf::Vector2f req = sf::Vector2f(40.f, 0.f);

	///////////////////////////
	//// Hair Cutting
	auto ht_label = sfg::Label::Create();
	auto ht_adj = sfg::Adjustment::Create(g_cfg.CUT_USE_TIME, 0.1f, 5.f, 0.1f, 0.1f);
	mCutTimeEntry = sfg::Entry::Create();
	mCutHairSlider = sfg::Scale::Create();

	// Set the labels
	ht_label->SetText("Time consumed cutting hair");
	ht_label->SetRequisition(req);
	setEntryText(mCutTimeEntry.get(), g_cfg.CUT_USE_TIME);
	mCutTimeEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mCutTimeEntry->SetRequisition(req);

	// Configure the slider
	mCutHairSlider->SetAdjustment(ht_adj);
	mCutHairSlider->SetRequisition(sf::Vector2f(300.f, 0.f));
	mCutHairSlider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onCutHairTimeAdjust, this));


	///////////////////////
	//// Hair Coloring
	auto hc_label = sfg::Label::Create();
	auto hc_adj = sfg::Adjustment::Create(g_cfg.COLOR_USE_TIME, 0.1f, 5.f, 0.1f, 0.1f);
	mColorTimeEntry = sfg::Entry::Create();
	mColorSlider = sfg::Scale::Create();

	// Set the labels
	hc_label->SetText("Time consumed coloring hair");
	hc_label->SetRequisition(req);
	setEntryText(mColorTimeEntry.get(), g_cfg.COLOR_USE_TIME);
	mColorTimeEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mColorTimeEntry->SetRequisition(req);

	// Configure the slider
	mColorSlider->SetAdjustment(hc_adj);
	mColorSlider->SetRequisition(sf::Vector2f(300.f, 0.f));
	mColorSlider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onColorTimeAdjust, this));

	///////////////////////
	//// Hair Washing
	auto hw_label = sfg::Label::Create();
	auto hw_adj = sfg::Adjustment::Create(g_cfg.WASH_USE_TIME, 0.1f, 5.f, 0.1f, 1.f);
	mWashTimeEntry = sfg::Entry::Create();
	mWashSlider = sfg::Scale::Create();

	// Set the labels
	hw_label->SetText("Time consumed washing hair");
	hw_label->SetRequisition(req);
	setEntryText(mWashTimeEntry.get(), g_cfg.WASH_USE_TIME);
	mWashTimeEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mWashTimeEntry->SetRequisition(req);

	// Configure the slider
	mWashSlider->SetAdjustment(hw_adj);
	mWashSlider->SetRequisition(sf::Vector2f(300.f, 0.f));
	mWashSlider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onWashTimeAdjust, this));

	///////////////////////
	//// Register use time
	auto ru_adj = sfg::Adjustment::Create(g_cfg.REGISTER_USE_TIME, 0.1f, 5.f, 0.1f, 1.f);
	mRegisterUseEntry = sfg::Entry::Create();
	mRegisterUseTimeScale = sfg::Scale::Create();

	// Set the labels
	setEntryText(mRegisterUseEntry.get(), g_cfg.REGISTER_USE_TIME);
	mRegisterUseEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mRegisterUseEntry->SetRequisition(req);

	// Configure the slider
	mRegisterUseTimeScale->SetAdjustment(ru_adj);
	mRegisterUseTimeScale->SetRequisition(sf::Vector2f(300.f, 0.f));
	mRegisterUseTimeScale->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onRegUseTimeAdjust, this));

	///////////////////////
	//// Customer Walking Speed scale
	auto cw_adj = sfg::Adjustment::Create(g_cfg.CUSTOMER_SPEED_MULTIPLIER, 0.1f, 2.f, 0.1f, 0.1f);
	mCustSpeedMultEntry = sfg::Entry::Create();
	mCustSpeedMultSlider = sfg::Scale::Create();

	// Set the labels
	setEntryText(mCustSpeedMultEntry.get(), g_cfg.CUSTOMER_SPEED_MULTIPLIER);
	mCustSpeedMultEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mCustSpeedMultEntry->SetRequisition(req);

	// Configure the slider
	mCustSpeedMultSlider->SetAdjustment(cw_adj);
	mCustSpeedMultSlider->SetRequisition(sf::Vector2f(300.f, 0.f));
	mCustSpeedMultSlider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onCustSpeedMultAdjust, this));

	///////////////////////
	//// State Tick Multiplier
	auto st_adj = sfg::Adjustment::Create(g_cfg.STATE_CHANGE_COOLDOWN_MULTIPLIER, 0.1f, 2.f, 0.1f, 0.1f);
	mStateTickMultEntry = sfg::Entry::Create();
	mStateTickMultScale = sfg::Scale::Create();

	// Set the labels
	setEntryText(mStateTickMultEntry.get(), g_cfg.STATE_CHANGE_COOLDOWN_MULTIPLIER);
	mStateTickMultEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mStateTickMultEntry->SetRequisition(req);

	// Configure the slider
	mStateTickMultScale->SetAdjustment(st_adj);
	mStateTickMultScale->SetRequisition(sf::Vector2f(300.f, 0.f));
	mStateTickMultScale->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onStateTickMultAdjust, this));

	///////////////////////
	//// Patience Penalty Multiplier
	auto pp_adj = sfg::Adjustment::Create(g_cfg.PATIENCE_PENALTY_MULTIPLIER, 0.1f, 2.f, 0.1f, 0.1f);
	mPatiencePenaltyMultEntry = sfg::Entry::Create();
	mPatiencePenaltyMultScale = sfg::Scale::Create();

	// Set the labels
	setEntryText(mPatiencePenaltyMultEntry.get(), g_cfg.PATIENCE_PENALTY_MULTIPLIER);
	mPatiencePenaltyMultEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mPatiencePenaltyMultEntry->SetRequisition(req);

	// Configure the slider
	mPatiencePenaltyMultScale->SetAdjustment(pp_adj);
	mPatiencePenaltyMultScale->SetRequisition(sf::Vector2f(300.f, 0.f));
	mPatiencePenaltyMultScale->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onPatiencePenaltyMultAdjust, this));

	///////////////////////
	//// Customer release interval
	auto cr_adj = sfg::Adjustment::Create(g_cfg.CUSTOMER_RELEASE_INTERVAL, 1.f, 20.f, 0.5f, 0.5f);
	mCustReleaseTickEntry = sfg::Entry::Create();
	mCustReleaseTickScale = sfg::Scale::Create();

	// Set the labels
	setEntryText(mCustReleaseTickEntry.get(), g_cfg.CUSTOMER_RELEASE_INTERVAL);
	mCustReleaseTickEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mCustReleaseTickEntry->SetRequisition(req);

	// Configure the slider
	mCustReleaseTickScale->SetAdjustment(cr_adj);
	mCustReleaseTickScale->SetRequisition(sf::Vector2f(300.f, 0.f));
	mCustReleaseTickScale->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onCustReleaseTickAdjust, this));

	// Remaining allocation
	mAllocationPointsEntry = sfg::Entry::Create(std::to_string(g_cfg.ALLOCATION_POINTS));
	mAllocationPointsEntry->SetState(sfg::Widget::State::INSENSITIVE);


	//// Build the final table
	auto table = sfg::Table::Create();

	table->Attach(ht_label, sf::Rect<sf::Uint32>(1, 1, 1, 1));
	table->Attach(mCutTimeEntry, sf::Rect<sf::Uint32>(2, 1, 1, 1), sfg::Table::FILL);
	table->Attach(sfg::Label::Create("sec."), sf::Rect<sf::Uint32>(3, 1, 1, 1));
	table->Attach(mCutHairSlider, sf::Rect<sf::Uint32>(4, 1, 1, 1));
	
	table->Attach(hc_label, sf::Rect<sf::Uint32>(1, 2, 1, 1));
	table->Attach(mColorTimeEntry, sf::Rect<sf::Uint32>(2, 2, 1, 1));
	table->Attach(sfg::Label::Create("sec."), sf::Rect<sf::Uint32>(3, 2, 1, 1));
	table->Attach(mColorSlider, sf::Rect<sf::Uint32>(4, 2, 1, 1));
	
	table->Attach(hw_label, sf::Rect<sf::Uint32>(1, 3, 1, 1));
	table->Attach(mWashTimeEntry, sf::Rect<sf::Uint32>(2, 3, 1, 1));
	table->Attach(sfg::Label::Create("sec."), sf::Rect<sf::Uint32>(3, 3, 1, 1));
	table->Attach(mWashSlider, sf::Rect<sf::Uint32>(4, 3, 1, 1));

	table->Attach(sfg::Label::Create("Time to cash out"), sf::Rect<sf::Uint32>(1, 4, 1, 1));
	table->Attach(mRegisterUseEntry, sf::Rect<sf::Uint32>(2, 4, 1, 1));
	table->Attach(sfg::Label::Create("sec."), sf::Rect<sf::Uint32>(3, 4, 1, 1));
	table->Attach(mRegisterUseTimeScale, sf::Rect<sf::Uint32>(4, 4, 1, 1));

	table->Attach(sfg::Label::Create("Speed multiplier"), sf::Rect<sf::Uint32>(1, 5, 1, 1));
	table->Attach(mCustSpeedMultEntry, sf::Rect<sf::Uint32>(2, 5, 1, 1));
	table->Attach(sfg::Label::Create("x"), sf::Rect<sf::Uint32>(3, 5, 1, 1));
	table->Attach(mCustSpeedMultSlider, sf::Rect<sf::Uint32>(4, 5, 1, 1));

	table->Attach(sfg::Label::Create("Patience cooldown multiplier"), sf::Rect<sf::Uint32>(1, 6, 1, 1));
	table->Attach(mStateTickMultEntry, sf::Rect<sf::Uint32>(2, 6, 1, 1));
	table->Attach(sfg::Label::Create("x"), sf::Rect<sf::Uint32>(3, 6, 1, 1));
	table->Attach(mStateTickMultScale, sf::Rect<sf::Uint32>(4, 6, 1, 1));

	table->Attach(sfg::Label::Create("Patience penalty multiplier"), sf::Rect<sf::Uint32>(1, 7, 1, 1));
	table->Attach(mPatiencePenaltyMultEntry, sf::Rect<sf::Uint32>(2, 7, 1, 1));
	table->Attach(sfg::Label::Create("x"), sf::Rect<sf::Uint32>(3, 7, 1, 1));
	table->Attach(mPatiencePenaltyMultScale, sf::Rect<sf::Uint32>(4, 7, 1, 1));

	table->Attach(sfg::Label::Create("Customer arrival delay"), sf::Rect<sf::Uint32>(1, 8, 1, 1));
	table->Attach(mCustReleaseTickEntry, sf::Rect<sf::Uint32>(2, 8, 1, 1));
	table->Attach(sfg::Label::Create("sec."), sf::Rect<sf::Uint32>(3, 8, 1, 1));
	table->Attach(mCustReleaseTickScale, sf::Rect<sf::Uint32>(4, 8, 1, 1));

	// Configure the remaining allocation box
	table->Attach(sfg::Label::Create("Remaining Points"), sf::Rect<sf::Uint32>(1, 9, 1, 1));
	table->Attach(mAllocationPointsEntry, sf::Rect<sf::Uint32>(2, 9, 1, 1));

	
	table->SetColumnSpacings(15.f);
	table->SetRowSpacings(10.f);

	return table;
}

