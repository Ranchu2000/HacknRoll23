#include "imports.h"
#include "DEFINITIONS.h"
#include "GameState.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include "Player.h"

void GameState::initVariables()
{
	this->waveNum += 1;
	this->spawnTimerMax = 200 * 1 / this->waveNum;
	this->score = 0;
}

void GameState::initFonts()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void GameState::initPlayer()
{
	this->playerTex.loadFromFile(PLAYER_TEXTURE_SHEET);
	this->player = new Player(this->mapSize / 2 * this->gridSize, this->mapSize / 2 * this->gridSize, this->playerTex, this->upgradeCur);
}

void GameState::initGui()
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Background
	this->backgroundTexture.loadFromFile(GAME_BACKGROUND_FILEPATH);
	this->background.setTexture(this->backgroundTexture);
	this->background.setPosition(0.f, 0.f);


	// View
	this->view.setSize((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT));
	this->view.setCenter((int)(this->mapSize / 2) * this->gridSize, (int)(this->mapSize / 2) * this->gridSize);


	//png are 128 pixels
	this->pauseText.loadFromFile(PAUSE_ICON_FILEPATH);
	this->pauseButton.setTexture(this->pauseText);
	this->pauseButton.setScale(Vector2f(1.f, 1.f));
	this->pauseButton.setPosition(gui::p2pX(95.f, vm) - this->pauseButton.getGlobalBounds().width / 2, gui::p2pY(0.f, vm));


	//hp
	this->hp.setFont(this->font);
	this->hp.setCharacterSize(gui::calcCharSize(vm, 45));
	this->hp.setFillColor(Color(DARK_GREY_COLOR));
	this->hp.setStyle(Text::Bold);
	this->hp.setString("HP");
	this->hp.setPosition(gui::p2pX(1.f, vm), gui::p2pY(0.f, vm));



	this->hpMaxBar.setPosition(gui::p2pX(2.f, vm) + this->hp.getGlobalBounds().width, gui::p2pY(1.f, vm));
	this->hpMaxBar.setFillColor(Color::White);
	this->hpMaxBar.setSize(Vector2f((gui::p2pX(1.25f, vm) * this->player->getAttributeComponent()->getMaxHealth()) + gui::p2pX(.5f, vm), gui::p2pY(5.5f, vm)));

	this->hpCurBar.setPosition(gui::p2pX(2.25f, vm) + this->hp.getGlobalBounds().width, gui::p2pY(1.25f, vm));
	this->hpCurBar.setFillColor(Color(GREEN_COLOR));

	this->hpText.setFont(this->font);
	this->hpText.setCharacterSize(gui::calcCharSize(vm, 45));
	this->hpText.setFillColor(Color(DARK_GREY_COLOR));
	this->hpText.setStyle(Text::Bold);
	this->hpText.setPosition(gui::p2pX(7.5f, vm) + this->hpMaxBar.getGlobalBounds().width, gui::p2pY(0.f, vm));

	//Wave
	this->waveText.setFont(this->font);
	this->waveText.setCharacterSize(gui::calcCharSize(vm, 45));
	this->waveText.setFillColor(Color(DARK_GREY_COLOR));
	this->waveText.setStyle(Text::Bold);
	this->waveText.setString("Wave " + std::to_string(this->waveNum));
	this->waveText.setPosition(gui::p2pX(75.f, vm) - this->waveText.getGlobalBounds().width / 2, gui::p2pY(0.f, vm));

}

void GameState::resetGui()
{
}

GameState::GameState(StateData* state_data, std::map<std::string,int> upgradeCur,  int waveNum) : State(state_data), upgradeCur(upgradeCur), waveNum(waveNum)
{
	this->initVariables();
	this->initFonts();
	this->initPlayer();
	this->initGui();
}

GameState::~GameState()
{
}

void GameState::updateInput(const float& dt)
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->hpCurBar.setSize(Vector2f((gui::p2pX(1.25f, vm) * this->player->getAttributeComponent()->getCurHealth()), gui::p2pY(5.f, vm)));
	this->hpText.setString(std::to_string(this->player->getAttributeComponent()->getCurHealth()) + "/" + std::to_string(this->player->getAttributeComponent()->getMaxHealth()));

}

void GameState::updatePlayerInput(const float& dt)
{
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		this->player->getMovementComponent()->stopVelocity();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Left
	{
		this->player->move(-1000.f, 0.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Right
	{
		this->player->move(1000.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Up
	{
		this->player->move(0.f, -1000.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Down
	{
		this->player->move(0.f, 1000.f, dt);
	}
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePosView, this->view);
	this->player->checkCollision(dt);
}

void GameState::updateView(const float& dt)
{
	// Setting the view to be at the player
	this->view.setCenter(this->player->getPosition().x + this->player->getGlobalBounds().width / 2, this->player->getPosition().y + this->player->getGlobalBounds().height / 2);
	
	// View Collision
	//Left collision
	if (this->view.getCenter().x - this->view.getSize().x / 2 < 0.f)
		this->view.setCenter(this->view.getSize().x / 2, this->view.getCenter().y);
	//Top collision
	if (this->view.getCenter().y - this->view.getSize().y / 2 < 0.f)
		this->view.setCenter(this->view.getCenter().x, this->view.getSize().y / 2);
	//Right collision
	if (this->view.getCenter().x + this->view.getSize().x / 2 > ((this->mapSize) * this->gridSize))
		this->view.setCenter(((this->mapSize) * this->gridSize) - (this->view.getSize().x / 2), this->view.getCenter().y);
	//Bottom collision
	if (this->view.getCenter().y + this->view.getSize().y / 2 > ((this->mapSize) * this->gridSize))
		this->view.setCenter(this->view.getCenter().x, ((this->mapSize) * this->gridSize) - (this->view.getSize().y / 2));
}

void GameState::updateCollision(const float& dt)
{
}

void GameState::updateButtons()
{
	
}

void GameState::updateGameState(const float& dt)
{
	if (this->player->getAttributeComponent()->getCurHealth() <= 0)
	{
		this->states->push(new GameOverState(this->stateData, this->score, this->waveNum));
		this->endState();
	}
	
	if (this->enemiesLeft == 0 && this->waveNum == 5)
	{
		this->states->push(new VictoryState(this->stateData));
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateButtons();
	this->updateInput(dt);
	if (!this->paused)
	{
		this->updatePlayerInput(dt);
		this->updatePlayer(dt);
		this->updateView(dt);
		this->updateGameState(dt);
	}
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	// DRAWING GAME
	target->setView(this->view);
	target->draw(this->background);

	this->player->render(*target);

	// DRAWING UI
	target->setView(target->getDefaultView());
	target->draw(this->hp);
	target->draw(this->hpMaxBar);
	target->draw(this->hpCurBar);
	target->draw(this->hpText);
	target->draw(this->waveText);
	target->draw(this->enemiesText);
	target->draw(this->pauseButton);
}
