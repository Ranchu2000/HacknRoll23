#include "SplashState.h"
#include "DEFINITIONS.h"

void SplashState::initVariables()
{
	this->timeShown = 0.0;
}



void SplashState::initGui() //init GUI
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);

	this->background.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	this->background.setFillColor(Color::Black);

	this->logoTexture.loadFromFile(LOGO_FILEPATH);
	this->logo.setTexture(this->logoTexture);
	this->logo.setPosition(gui::p2pX(50.0f, vm) - this->logo.getGlobalBounds().width / 2, gui::p2pY(37.0f, vm) - this->logo.getGlobalBounds().height / 2);

	this->titleTexture.loadFromFile(TITLE_FILEPATH);
	this->title.setTexture(this->titleTexture);
	this->title.setPosition(gui::p2pX(50.0f, vm) - this->title.getGlobalBounds().width / 2, gui::p2pY(55.0f, vm) - this->title.getGlobalBounds().height / 2);
}


SplashState::SplashState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initGui();
}

SplashState::~SplashState()
{
}

void SplashState::update(const float& dt)
{
	this->timeShown += dt;
	if (this->timeShown > SPLASH_TIME)
		this->endState();
}


void SplashState::render(sf::RenderTarget* target) //draw stuff
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->logo);
	target->draw(this->title);
}
