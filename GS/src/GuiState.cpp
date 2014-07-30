#include "GuiState.h"
#include "GlobalConfig.h"
#include "Glob.h"
#include <string>

GuiState::GuiState(StateStack& stack, Context context)
: State(stack, context)
{
	initalize();
}

void GuiState::initalize()
{
	GlobalConfig& g_cfg = GlobalConfig::get();

	mWindow = sfg::Window::Create();
	mWindow->SetTitle("Hello world");
	mDesktop.Add(mWindow);
	
	// Generate the Bottom Box that holds the buttons
	auto button_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 0.5f);
	mExitButton = sfg::Button::Create("Save");
	mExitButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GuiState::onExitButtonClicked, this));
	
	mCancelButton = sfg::Button::Create("Cancel");
	mCancelButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GuiState::onCancelButtonClicked, this));

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
}

// Get the remaining allocation points
float GuiState::getRemainingAllocationPoints()
{
	return std::stof(mAllocationPointsEntry->GetText().toAnsiString());

}

// Set the allocation points
void GuiState::setRemainingAllocationPoints(float points)
{
	std::ostringstream oss;
	oss << points;
	mAllocationPointsEntry->SetText(oss.str());

}

// Check the allocation and remove points
bool GuiState::checkAllocation(float cost)
{
	float points = getRemainingAllocationPoints();
	std::cout << points << std::endl;
	if (cost > points)
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

void GuiState::onCutHairTimeAdjust()
{
	// Cost, unit is per tenth of a second
	float cost = 10.f;
	float val = mCutHairSlider->GetValue();
	float chg = (std::stof(mCutTimeEntry->GetText().toAnsiString())) - mCutHairSlider->GetAdjustment()->GetValue() * 10;
	std::cout << "Cost: " << cost << " Chg: " << chg << std::endl;
	if (checkAllocation(cost * chg))
	{
		mCutTimeEntry->SetText(std::to_string(val));
	}
	else
	{
		mCutTimeEntry->SetText(std::to_string(val - chg));
		mCutHairSlider->SetValue(val - chg);
	}

}

void GuiState::onWashTimeAdjust()
{
	float val = mWashSlider->GetValue();
	mWashTimeEntry->SetText(std::to_string(val));
}

void GuiState::onCustSpeedMultAdjust()
{
	mCustSpeedMultEntry->SetText(std::to_string(mCustSpeedMultSlider->GetValue()));

}

void GuiState::onColorTimeAdjust()
{
	float val = mColorSlider->GetValue();
	mColorTimeEntry->SetText(std::to_string(val));

}

void GuiState::onRegUseTimeAdjust()
{
	mRegisterUseEntry->SetText(std::to_string(mRegisterUseTimeScale->GetValue()));
}

void GuiState::onStateTickMultAdjust()
{
	mStateTickMultEntry->SetText(std::to_string(mStateTickMultScale->GetValue()));
}

void GuiState::onPatiencePenaltyMultAdjust()
{
	mPatiencePenaltyMultEntry->SetText(std::to_string(mPatiencePenaltyMultScale->GetValue()));
}

void GuiState::onCustReleaseTickAdjust()
{
	mCustReleaseTickEntry->SetText(std::to_string(mCustReleaseTickScale->GetValue()));
}

sfg::Table::Ptr GuiState::getSliderSettings()
{
	GlobalConfig& g_cfg = GlobalConfig::get();	

	sf::Vector2f req = sf::Vector2f(100.f, 0.f);

	///////////////////////////
	//// Hair Cutting
	auto ht_label = sfg::Label::Create();
	auto ht_adj = sfg::Adjustment::Create(g_cfg.CUT_USE_TIME, 0.f, 15.f, 0.1f, 1.f);
	mCutTimeEntry = sfg::Entry::Create();
	mCutHairSlider = sfg::Scale::Create();

	// Set the labels
	ht_label->SetText("Time consumed cutting hair");
	ht_label->SetRequisition(req);
	mCutTimeEntry->SetText(std::to_string(g_cfg.CUT_USE_TIME));
	mCutTimeEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mCutTimeEntry->SetRequisition(req);

	// Configure the slider
	mCutHairSlider->SetAdjustment(ht_adj);
	mCutHairSlider->SetRequisition(sf::Vector2f(400.f, 0.f));
	mCutHairSlider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onCutHairTimeAdjust, this));


	///////////////////////
	//// Hair Coloring
	auto hc_label = sfg::Label::Create();
	auto hc_adj = sfg::Adjustment::Create(g_cfg.COLOR_USE_TIME, 0.f, 15.f, 0.1f, 1.f);
	mColorTimeEntry = sfg::Entry::Create();
	mColorSlider = sfg::Scale::Create();

	// Set the labels
	hc_label->SetText("Time consumed coloring hair");
	hc_label->SetRequisition(req);
	mColorTimeEntry->SetText(std::to_string(g_cfg.COLOR_USE_TIME));
	mColorTimeEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mColorTimeEntry->SetRequisition(req);

	// Configure the slider
	mColorSlider->SetAdjustment(hc_adj);
	mColorSlider->SetRequisition(sf::Vector2f(400.f, 0.f));
	mColorSlider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onColorTimeAdjust, this));

	///////////////////////
	//// Hair Washing
	auto hw_label = sfg::Label::Create();
	auto hw_adj = sfg::Adjustment::Create(g_cfg.WASH_USE_TIME, 0.f, 15.f, 0.1f, 1.f);
	mWashTimeEntry = sfg::Entry::Create();
	mWashSlider = sfg::Scale::Create();

	// Set the labels
	hw_label->SetText("Time consumed washing hair");
	hw_label->SetRequisition(req);
	mWashTimeEntry->SetText(std::to_string(g_cfg.WASH_USE_TIME));
	mWashTimeEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mWashTimeEntry->SetRequisition(req);

	// Configure the slider
	mWashSlider->SetAdjustment(hw_adj);
	mWashSlider->SetRequisition(sf::Vector2f(400.f, 0.f));
	mWashSlider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onWashTimeAdjust, this));

	///////////////////////
	//// Register use time
	auto ru_adj = sfg::Adjustment::Create(g_cfg.REGISTER_USE_TIME, 0.1f, 5.f, 0.1f, 1.f);
	mRegisterUseEntry = sfg::Entry::Create();
	mRegisterUseTimeScale = sfg::Scale::Create();

	// Set the labels
	mRegisterUseEntry->SetText(std::to_string(g_cfg.CUSTOMER_SPEED_MULTIPLIER));
	mRegisterUseEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mRegisterUseEntry->SetRequisition(req);

	// Configure the slider
	mRegisterUseTimeScale->SetAdjustment(ru_adj);
	mRegisterUseTimeScale->SetRequisition(sf::Vector2f(400.f, 0.f));
	mRegisterUseTimeScale->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onRegUseTimeAdjust, this));

	///////////////////////
	//// Customer Walking Speed scale
	auto cw_adj = sfg::Adjustment::Create(g_cfg.CUSTOMER_SPEED_MULTIPLIER, 0.1f, 5.f, 0.1f, 1.f);
	mCustSpeedMultEntry = sfg::Entry::Create();
	mCustSpeedMultSlider = sfg::Scale::Create();

	// Set the labels
	mCustSpeedMultEntry->SetText(std::to_string(g_cfg.CUSTOMER_SPEED_MULTIPLIER));
	mCustSpeedMultEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mCustSpeedMultEntry->SetRequisition(req);

	// Configure the slider
	mCustSpeedMultSlider->SetAdjustment(cw_adj);
	mCustSpeedMultSlider->SetRequisition(sf::Vector2f(400.f, 0.f));
	mCustSpeedMultSlider->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onCustSpeedMultAdjust, this));

	///////////////////////
	//// State Tick Multiplier
	auto st_adj = sfg::Adjustment::Create(g_cfg.STATE_CHANGE_COOLDOWN_MULTIPLIER, 1.f, 200.f, 0.5f, 1.f);
	mStateTickMultEntry = sfg::Entry::Create();
	mStateTickMultScale = sfg::Scale::Create();

	// Set the labels
	mStateTickMultEntry->SetText(std::to_string(g_cfg.STATE_CHANGE_COOLDOWN_MULTIPLIER));
	mStateTickMultEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mStateTickMultEntry->SetRequisition(req);

	// Configure the slider
	mStateTickMultScale->SetAdjustment(st_adj);
	mStateTickMultScale->SetRequisition(sf::Vector2f(400.f, 0.f));
	mStateTickMultScale->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onStateTickMultAdjust, this));

	///////////////////////
	//// Patience Penalty Multiplier
	auto pp_adj = sfg::Adjustment::Create(g_cfg.PATIENCE_PENALTY_MULTIPLIER, 1.f, 200.f, 0.5f, 1.f);
	mPatiencePenaltyMultEntry = sfg::Entry::Create();
	mPatiencePenaltyMultScale = sfg::Scale::Create();

	// Set the labels
	mPatiencePenaltyMultEntry->SetText(std::to_string(g_cfg.PATIENCE_PENALTY_MULTIPLIER));
	mPatiencePenaltyMultEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mPatiencePenaltyMultEntry->SetRequisition(req);

	// Configure the slider
	mPatiencePenaltyMultScale->SetAdjustment(pp_adj);
	mPatiencePenaltyMultScale->SetRequisition(sf::Vector2f(400.f, 0.f));
	mPatiencePenaltyMultScale->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onPatiencePenaltyMultAdjust, this));

	///////////////////////
	//// Customer release interval
	auto cr_adj = sfg::Adjustment::Create(g_cfg.CUSTOMER_RELEASE_INTERVAL, 1.f, 20.f, 0.1f, 1.f);
	mCustReleaseTickEntry = sfg::Entry::Create();
	mCustReleaseTickScale = sfg::Scale::Create();

	// Set the labels
	mCustReleaseTickEntry->SetText(std::to_string(g_cfg.CUSTOMER_RELEASE_INTERVAL));
	mCustReleaseTickEntry->SetState(sfg::Widget::State::INSENSITIVE);
	mCustReleaseTickEntry->SetRequisition(req);

	// Configure the slider
	mCustReleaseTickScale->SetAdjustment(cr_adj);
	mCustReleaseTickScale->SetRequisition(sf::Vector2f(400.f, 0.f));
	mCustReleaseTickScale->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(std::bind(&GuiState::onCustReleaseTickAdjust, this));


	//// Build the final table
	auto table = sfg::Table::Create();

	table->Attach(ht_label, sf::Rect<sf::Uint32>(1, 1, 1, 1));
	table->Attach(mCutTimeEntry, sf::Rect<sf::Uint32>(2, 1, 1, 1));
	table->Attach(mCutHairSlider, sf::Rect<sf::Uint32>(3, 1, 1, 1));
	
	table->Attach(hc_label, sf::Rect<sf::Uint32>(1, 2, 1, 1));
	table->Attach(mColorTimeEntry, sf::Rect<sf::Uint32>(2, 2, 1, 1));
	table->Attach(mColorSlider, sf::Rect<sf::Uint32>(3, 2, 1, 1));
	
	table->Attach(sfg::Label::Create("Register use time"), sf::Rect<sf::Uint32>(1, 3, 1, 1));
	table->Attach(mRegisterUseEntry, sf::Rect<sf::Uint32>(2, 3, 1, 1));
	table->Attach(mRegisterUseTimeScale, sf::Rect<sf::Uint32>(3, 3, 1, 1));
	
	table->Attach(hw_label, sf::Rect<sf::Uint32>(1, 4, 1, 1));
	table->Attach(mWashTimeEntry, sf::Rect<sf::Uint32>(2, 4, 1, 1));
	table->Attach(mWashSlider, sf::Rect<sf::Uint32>(3, 4, 1, 1));

	table->Attach(sfg::Label::Create("Speed multiplier"), sf::Rect<sf::Uint32>(1, 5, 1, 1));
	table->Attach(mCustSpeedMultEntry, sf::Rect<sf::Uint32>(2, 5, 1, 1));
	table->Attach(mCustSpeedMultSlider, sf::Rect<sf::Uint32>(3, 5, 1, 1));

	table->Attach(sfg::Label::Create("Patience cooldown multiplier"), sf::Rect<sf::Uint32>(1, 6, 1, 1));
	table->Attach(mStateTickMultEntry, sf::Rect<sf::Uint32>(2, 6, 1, 1));
	table->Attach(mStateTickMultScale, sf::Rect<sf::Uint32>(3, 6, 1, 1));

	table->Attach(sfg::Label::Create("Patience penalty multiplier"), sf::Rect<sf::Uint32>(1, 7, 1, 1));
	table->Attach(mPatiencePenaltyMultEntry, sf::Rect<sf::Uint32>(2, 7, 1, 1));
	table->Attach(mPatiencePenaltyMultScale, sf::Rect<sf::Uint32>(3, 7, 1, 1));

	table->Attach(sfg::Label::Create("Customer release rate"), sf::Rect<sf::Uint32>(1, 8, 1, 1));
	table->Attach(mCustReleaseTickEntry, sf::Rect<sf::Uint32>(2, 8, 1, 1));
	table->Attach(mCustReleaseTickScale, sf::Rect<sf::Uint32>(3, 8, 1, 1));


	
	table->SetColumnSpacings(15.f);
	table->SetRowSpacings(5.f);

	return table;
}

