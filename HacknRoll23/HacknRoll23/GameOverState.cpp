#include "GameOverState.h"

void GameOverState::initVariables()
{
	this->initialStats["Attack"] = 0;
	this->initialStats["Health"] = 0;
	this->initialStats["Speed"] = 0;
	this->initialStats["Firing"] = 0;
	this->initialStats["Burn"] = 0;
	this->initialStats["Pierce"] = 0;
}

void GameOverState::initFont()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void GameOverState::initGui() //init GUI
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);

	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(Color(DARK_BLUE_COLOR));


	//Title
	this->title.setFont(this->font);
	this->title.setCharacterSize(gui::calcCharSize(vm, 22));
	this->title.setFillColor(Color(GOLD_COLOR));
	this->title.setStyle(Text::Bold);
	this->title.setString("Game Over");
	this->title.setPosition(gui::p2pX(54.5f, vm) - this->title.getGlobalBounds().width * 3 / 4, gui::p2pY(20.f, vm));



	//Icon
	this->lossText.loadFromFile(LOSS_ICON_FILEPATH);
	this->lossIcon.setTexture(lossText);
	this->lossIcon.setScale(Vector2f(1.5f, 1.5f));
	this->lossIcon.setPosition(gui::p2pX(52.5f, vm) + this->title.getGlobalBounds().width / 3, gui::p2pY(20.f, vm));

	// Challenge
	this->challenge.setFont(this->font);
	this->challenge.setCharacterSize(gui::calcCharSize(vm, 30));
	this->challenge.setFillColor(Color(RED_COLOR));
	this->challenge.setStyle(Text::Bold);
	this->challenge.setString("Timmy was rejected.");
	this->challenge.setPosition(gui::p2pX(50.0f, vm) - this->challenge.getGlobalBounds().width / 2, gui::p2pY(40.f, vm));

	//Text
	this->text.setFont(this->font);
	this->text.setCharacterSize(gui::calcCharSize(vm, 40));
	this->text.setFillColor(Color(RED_COLOR));
	this->text.setStyle(Text::Regular);
	std::string stats = "Waves Cleared: " + std::to_string(this->waves) + "\nEnemies Defeated: " + std::to_string(this->enemies);
	this->text.setString(stats);
	this->text.setPosition(gui::p2pX(50.0f, vm) - this->text.getGlobalBounds().width / 2, gui::p2pY(55.f, vm));



	//png are 128 pixels
	this->retryText.loadFromFile(RETRY_ICON_FILEPATH);
	this->retryBtn.setTexture(this->retryText);
	this->retryBtn.setScale(Vector2f(1.25f, 1.25f));
	this->retryBtn.setPosition(gui::p2pX(40.f, vm) - this->retryBtn.getGlobalBounds().width / 2, gui::p2pY(85.f, vm) - this->retryBtn.getGlobalBounds().height / 2);

	this->homeText.loadFromFile(HOME_ICON_FILEPATH);
	this->homeBtn.setTexture(this->homeText);
	this->homeBtn.setScale(Vector2f(1.25f, 1.25f));
	this->homeBtn.setPosition(gui::p2pX(60.f, vm) - this->homeBtn.getGlobalBounds().width / 2, gui::p2pY(85.f, vm) - this->homeBtn.getGlobalBounds().height / 2);
}


GameOverState::GameOverState(StateData* state_data, int score, int waveNum)
	: State(state_data), enemies(score), waves(waveNum)
{
	this->initVariables();
	this->initFont();
	this->initGui();
}

GameOverState::~GameOverState()
{
}

void GameOverState::updateInput(const float& dt)
{
	if (gui::isSpriteClicked(this->retryBtn, sf::Mouse::Left, *this->window)) {
		std::cout << "New Game" << std::endl;
		this->states->push(new GameState(this->stateData, this->initialStats, 0));
		//GameState
		this->endState();
	}

	if (gui::isSpriteClicked(this->homeBtn, sf::Mouse::Left, *this->window)) {
		std::cout << "Return to Main Menu" << std::endl;
		this->states->push(new MainMenuState(this->stateData));
		this->endState();
	}
}

void GameOverState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
}


void GameOverState::render(sf::RenderTarget* target) //draw stuff
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->title);
	target->draw(this->challenge);
	target->draw(this->text);
	target->draw(this->lossIcon);
	target->draw(this->retryBtn);
	target->draw(this->homeBtn);
}
