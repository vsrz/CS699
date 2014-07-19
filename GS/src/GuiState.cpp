#include "GuiState.h"
#include "Glob.h"

GuiState::GuiState(StateStack& stack, Context context)
: State(stack, context)
{
	initalize();
}

void GuiState::initalize()
{
	mWindow = sfg::Window::Create();
	mWindow->SetTitle("Hello world");
	mWindow->SetPosition( sf::Vector2f(25.f, 25.f));
	//mWindow->SetRequisition(sf::Vector2f(800.f, 480.f));
	mDesktop.Add(mWindow);
	
	
	auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 0.5f);
	mExitButton = sfg::Button::Create("Exit");
	box->Pack(mExitButton);
	mExitButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&GuiState::onExitButtonClicked, this));


	mLabel = sfg::Label::Create();
	mLabel->SetText("Hello World");
	box->Pack(mLabel);
	mWindow->Add(box);
}

void GuiState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.resetGLStates();
	mSfgui.Display(window);
}

bool GuiState::update(sf::Time dt)
{
	mDesktop.Update(dt.asSeconds());
	return false;
}

bool GuiState::handleEvent(const sf::Event& event)
{
	
	mDesktop.HandleEvent(event);
	return false;
}


void GuiState::onExitButtonClicked()
{
	requestStackPop();
}
