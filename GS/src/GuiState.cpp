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
	mWindow->SetPosition( sf::Vector2f(0.f, 0.f));
	mWindow->SetRequisition(sf::Vector2f(1280.f, 720.f));
	mDesktop.Add(mWindow);
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 0.5f);
	mButton = sfg::Button::Create("Click");
	box->Pack(mButton);
	mLabel = sfg::Label::Create();
	mLabel->SetText("Hello World");
	box->Pack(mLabel);
	mDesktop.Add(box);
}

void GuiState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.resetGLStates();
	mSfgui.Display(window);
}

bool GuiState::update(sf::Time dt)
{
	//mWindow->Update(dt.asSeconds());
	mDesktop.Update(dt.asSeconds());
	return false;
}

bool GuiState::handleEvent(const sf::Event& event)
{
	
	if (event.key.code == sf::Keyboard::Escape)
	{
		std::cout << "Stack pop\n";
		requestStackPop();
	}
	mDesktop.HandleEvent(event);
	return false;
}



