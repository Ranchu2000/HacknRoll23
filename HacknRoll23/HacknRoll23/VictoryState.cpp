#include "VictoryState.h"

void VictoryState::initVariables()
{
	this->gamesounds = new GameSounds();
	this->gamesounds->VictoryMusic.play();
}

void VictoryState::initFont()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void VictoryState::initGui() //init GUI
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setPosition((SCREEN_WIDTH / 2) - (this->background.getGlobalBounds().width / 2), SCREEN_HEIGHT / 2 - (this->background.getGlobalBounds().height / 2));
	this->background.setFillColor(Color(DARK_BLUE_COLOR));



	//Title
	this->title.setFont(this->font);
	this->title.setCharacterSize(gui::calcCharSize(vm, 15));
	this->title.setFillColor(Color(GOLD_COLOR));
	this->title.setStyle(Text::Bold);
	this->title.setString("Victory");
	this->title.setPosition(gui::p2pX(50.0f, vm) - this->title.getGlobalBounds().width * 3 / 4, gui::p2pY(20.f, vm));

	//Icon
	this->wonText.loadFromFile(WON_ICON_FILEPATH);
	this->wonIcon.setTexture(this->wonText);
	this->wonIcon.setScale(Vector2f(1.75f, 1.75f));
	this->wonIcon.setPosition(gui::p2pX(50.0f, vm) + this->title.getGlobalBounds().width / 3, gui::p2pY(22.f, vm));

	//Text
	this->text.setFont(this->font);
	this->text.setCharacterSize(gui::calcCharSize(vm, 30));
	this->text.setFillColor(Color(RED_COLOR));
	this->text.setStyle(Text::Bold);
	this->text.setString("Timmy was accepted :D");
	this->text.setPosition(gui::p2pX(50.0f, vm) - this->text.getGlobalBounds().width / 2, gui::p2pY(45.f, vm));

	//prizeInstructions
	this->prizeInstructions.setFont(this->font);
	this->prizeInstructions.setCharacterSize(gui::calcCharSize(vm, 50));
	this->prizeInstructions.setFillColor(Color(RED_COLOR));
	this->prizeInstructions.setStyle(Text::Regular);
	this->prizeInstructions.setString("Collect your prize --->");
	this->prizeInstructions.setPosition(gui::p2pX(53.0f, vm) - this->text.getGlobalBounds().width / 2, gui::p2pY(65.f, vm));

	//prize
	this->prizeTexture.loadFromFile(PRIZE_ICON_FILEPATH);
	this->prize.setTexture(&this->prizeTexture);
	this->prize.setSize(Vector2f(30.f * 6, 37.f * 6));
	this->prize.setPosition(Vector2f(gui::p2pX(70.0f, vm) - this->prize.getGlobalBounds().height, gui::p2pY(58.0f, vm)));

	//png are 128 pixels
	this->homeText.loadFromFile(HOME_ICON_FILEPATH);
	this->homeBtn.setTexture(this->homeText);
	this->homeBtn.setScale(Vector2f(1.25f, 1.25f));
	this->homeBtn.setPosition(gui::p2pX(50.f, vm) - this->homeBtn.getGlobalBounds().width / 2, gui::p2pY(85.f, vm) - this->homeBtn.getGlobalBounds().height / 2);
}


VictoryState::VictoryState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFont();
	this->initGui();
}

VictoryState::~VictoryState()
{
}

void VictoryState::updateInput(const float& dt)
{
	if (gui::isSpriteClicked(this->homeBtn, sf::Mouse::Left, *this->window)) {
		std::cout << "Return to Main Menu" << std::endl;
		this->gamesounds->VictoryMusic.play();
		this->states->push(new MainMenuState(this->stateData));
		this->endState();
	}
}

void VictoryState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
}


void VictoryState::render(sf::RenderTarget* target) //draw stuff
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->title);
	target->draw(this->prizeInstructions);
	target->draw(this->prize);
	target->draw(this->text);
	target->draw(this->wonIcon);
	target->draw(this->homeBtn);
}
