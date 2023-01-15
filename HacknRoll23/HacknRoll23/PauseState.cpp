#include "PauseState.h"

//Initializer functions
void PauseState::initVariables()
{
}

void PauseState::initFonts()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void PauseState::initGui()
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setPosition(0.f, 0.f);
	this->background.setFillColor(Color(DARK_BLUE_COLOR));



	this->backgroundScreen.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->backgroundScreen.setPosition((SCREEN_WIDTH / 2) - (this->backgroundScreen.getGlobalBounds().width / 2), SCREEN_HEIGHT / 2 - (this->backgroundScreen.getGlobalBounds().height / 2));
	this->backgroundScreen.setFillColor(Color(DARK_BLUE_COLOR));

	//Title
	this->text.setFont(this->font);
	this->text.setCharacterSize(gui::calcCharSize(vm, 22));
	this->text.setFillColor(Color(GOLD_COLOR));
	this->text.setStyle(Text::Bold);
	this->text.setString("Game Paused");
	this->text.setPosition(gui::p2pX(50.0f, vm) - this->text.getGlobalBounds().width / 2, gui::p2pY(22.f, vm));


	//png are 128 pixels
	this->resumeText.loadFromFile(RESUME_ICON_FILEPATH);
	this->resumeButton.setTexture(this->resumeText);
	this->resumeButton.setScale(Vector2f(1.5f, 1.5f));
	this->resumeButton.setPosition(gui::p2pX(40.f, vm) - this->resumeButton.getGlobalBounds().width / 2, gui::p2pY(60.f, vm) - this->resumeButton.getGlobalBounds().height / 2);


	this->homeText.loadFromFile(HOME_ICON_FILEPATH);
	this->homeButton.setTexture(this->homeText);
	this->homeButton.setScale(Vector2f(1.5f, 1.5f));
	this->homeButton.setPosition(gui::p2pX(60.f, vm) - this->homeButton.getGlobalBounds().width / 2, gui::p2pY(60.f, vm) - this->homeButton.getGlobalBounds().height / 2);
}

PauseState::PauseState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initGui();
}

PauseState::~PauseState()
{
}


void PauseState::updateInput(const float& dt)
{
	if (gui::isSpriteClicked(this->resumeButton, sf::Mouse::Left, *this->window)) {
		this->endState();
	}

	if (gui::isSpriteClicked(this->homeButton, sf::Mouse::Left, *this->window)) {
		this->states->push(new MainMenuState(this->stateData));
		this->endState();
	}
}

void PauseState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
}

void PauseState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->backgroundScreen);
	target->draw(this->text);
	target->draw(this->homeButton);
	target->draw(this->resumeButton);
}