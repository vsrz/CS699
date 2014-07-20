#include "GuiState.h"
#include "GlobalConfig.h"
#include "Glob.h"

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


void GuiState::onExitButtonClicked()
{
	GlobalConfig& config = GlobalConfig::get();
	
	config.CUT_USE_TIME = mCutHairSlider->GetValue();
	config.WASH_USE_TIME = mWashSlider->GetValue();
	config.COLOR_USE_TIME= mColorSlider->GetValue();
	config.CUSTOMER_SPEED_MULTIPLIER = mCustSpeedMultSlider->GetValue();
	requestStackPop();
	
}

void GuiState::onCancelButtonClicked()
{
	requestStackPop();
}

void GuiState::onCutHairTimeAdjust()
{
	float val = mCutHairSlider->GetValue();
	mCutTimeEntry->SetText(std::to_string(val));

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

sfg::Table::Ptr GuiState::getSliderSettings()
{
	GlobalConfig& g_cfg = GlobalConfig::get();	

	sf::Vector2f req = sf::Vector2f(100.f, 0.f);

	///////////////////////////
	//// Hair Cutting
	auto ht_label = sfg::Label::Create();
	auto ht_adj = sfg::Adjustment::Create(g_cfg.CUT_USE_TIME, 0.f, 15.f, 0.25f, 1.f);
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
	auto hc_adj = sfg::Adjustment::Create(g_cfg.COLOR_USE_TIME, 0.f, 15.f, 0.25f, 1.f);
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
	auto hw_adj = sfg::Adjustment::Create(g_cfg.WASH_USE_TIME, 0.f, 15.f, 0.25f, 1.f);
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

	//// Build the final table
	auto table = sfg::Table::Create();

	table->Attach(ht_label, sf::Rect<sf::Uint32>(1, 1, 1, 1));
	table->Attach(mCutTimeEntry, sf::Rect<sf::Uint32>(2, 1, 1, 1));
	table->Attach(mCutHairSlider, sf::Rect<sf::Uint32>(3, 1, 1, 1));
	table->Attach(hc_label, sf::Rect<sf::Uint32>(1, 2, 1, 1));
	table->Attach(mColorTimeEntry, sf::Rect<sf::Uint32>(2, 2, 1, 1));
	table->Attach(mColorSlider, sf::Rect<sf::Uint32>(3, 2, 1, 1));
	table->Attach(hw_label, sf::Rect<sf::Uint32>(1, 3, 1, 1));
	table->Attach(mWashTimeEntry, sf::Rect<sf::Uint32>(2, 3, 1, 1));
	table->Attach(mWashSlider, sf::Rect<sf::Uint32>(3, 3, 1, 1));
	table->Attach(sfg::Label::Create("Speed multiplier"), sf::Rect<sf::Uint32>(1, 4, 1, 1));
	table->Attach(mCustSpeedMultEntry, sf::Rect<sf::Uint32>(2, 4, 1, 1));
	table->Attach(mCustSpeedMultSlider, sf::Rect<sf::Uint32>(3, 4, 1, 1));

	table->SetColumnSpacings(15.f);
	table->SetRowSpacings(5.f);

	return table;
}

