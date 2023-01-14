#include "MainMenuState.h"
#include "DEFINITIONS.h"

void MainMenuState::initVariables()
{
}

void MainMenuState::initFont()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void MainMenuState::initGui() //init GUI
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Background
	this->background.setSize(Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));
	this->background.setFillColor(Color(DARK_BLUE_COLOR));

	this->logoTexture.loadFromFile(LOGO_FILEPATH);
	this->logo.setTexture(this->logoTexture);
	this->logo.setPosition(gui::p2pX(8.f, vm), gui::p2pY(16.f, vm));

	this->instructionBackground.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	this->instructionBackground.setFillColor(Color(BROWN_COLOR));
	this->instructionBackground.setPosition(Vector2f(gui::p2pX(60.f,vm), 0.f));
}

void MainMenuState::resetGui() //reset UI
{
}

MainMenuState::MainMenuState(StateData* state_data) 
	: State(state_data)
{
	this->initVariables();
	this->initFont();
	this->initGui();
	this->resetGui();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons() //map buttons to functionality
{


}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	
}

void MainMenuState::render(sf::RenderTarget* target) //draw stuff
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->logo);
	target->draw(this->instructionBackground);
}
