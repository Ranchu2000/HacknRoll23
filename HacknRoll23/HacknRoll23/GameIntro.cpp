#include "GameIntro.h"
#include "imports.h"
#include "DEFINITIONS.h"

void GameIntro::initVariables()
{
}

void GameIntro::initFonts()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void GameIntro::initGui()
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(Color::Black);
	
	this->title.setFont(this->font);
	this->title.setCharacterSize(gui::calcCharSize(vm, 30));
	this->title.setFillColor(Color(RED_COLOR));
	this->title.setStyle(Text::Bold);
	this->title.setString("Game Introduction");
	this->title.setPosition(gui::p2pX(50.0f, vm)- this->title.getGlobalBounds().width/2, gui::p2pY(5.f, vm));

	this->gamePlayText.setFont(this->font);
	this->gamePlayText.setCharacterSize(gui::calcCharSize(vm, 30));
	this->gamePlayText.setFillColor(Color(RED_COLOR));
	this->gamePlayText.setStyle(Text::Bold);
	this->gamePlayText.setString("Timmy has to clear 5 waves of enemies in order to win. All enemies must be cleared in order to proceed to the next wave. Each wave will get increasingly difficult but fret not there are player upgrades given fduring the intermission state at the end of every wave.");
	this->gamePlayText.setPosition(gui::p2pX(50.0f, vm) - this->title.getGlobalBounds().width / 2, gui::p2pY(5.f, vm));

	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(gui::calcCharSize(vm, 50));
	this->enemyText.setFillColor(Color(RED_COLOR));
	this->enemyText.setStyle(Text::Regular);
	this->enemyText.setString("There are 2 types of enemies that Timmy will encounter, Melee and Ranged Enemies.");
	this->enemyText.setPosition(gui::p2pX(60.0f, vm) - this->title.getGlobalBounds().width / 2, gui::p2pY(5.f, vm));

	this->enemyMeleeTexture.loadFromFile("MELEE_ENEMY_FILEPATH");
	this->enemyMelee.setTexture(enemyMeleeTexture);
	this->enemyMelee.setPosition(0.f, 10.f);

	this->enemyRangedTexture.loadFromFile("RANGED_ENEMY_FILEPATH");
	this->enemyRanged.setTexture(enemyRangedTexture);	
	this->enemyRanged.setPosition(0.f, 20.f);

	this->enemyProjTexture.loadFromFile("ENEMY_PROJ_FILEPATH");
	this->enemyProj.setTexture(enemyProjTexture);
	this->enemyProj.setPosition(0.f, 30.f);
	
	this->playerText.setFont(this->font);
	this->playerText.setCharacterSize(gui::calcCharSize(vm, 50));
	this->playerText.setFillColor(Color(RED_COLOR));
	this->playerText.setStyle(Text::Regular);
	this->playerText.setString("Meet Timmy :) In the face of seemingly impossible firms, Timmy is armed with many copies of his resume which will be his ammunition. Both Timmy's player and resume stats can be upgraded during the wave intermission rounds");
	this->playerText.setPosition(gui::p2pX(80.0f, vm) - this->title.getGlobalBounds().width / 2, gui::p2pY(5.f, vm));

	this->playerTexture.loadFromFile("PLAYER_FILEPATH");
	this->player.setTexture(playerTexture);
	this->player.setPosition(0.f, 40.f);

	this->playerProjTexture.loadFromFile("PLAYER_PROJ_FILEPATH");
	this->playerProj.setTexture(playerProjTexture);
	this->playerProj.setPosition(0.f, 50.f);

	this->nextBtn= new gui::Button(
		gui::p2pX(75.f, vm), gui::p2pY(87.f, vm),
		gui::p2pX(23, vm), gui::p2pY(11.f, vm),
		&this->font, "Continue", gui::calcCharSize(vm, 35),
		Color(RED_COLOR), Color::White,
		Color::Black, Color::Black, Color(RED_COLOR));
}
void GameIntro::resetGui()
{
	delete this->nextBtn;
	this->initGui();
}

GameIntro::GameIntro(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initGui();
	this->resetGui();
}

GameIntro::~GameIntro()
{
	delete this->nextBtn;
}

void GameIntro::updateInput(const float& dt)
{}

void GameIntro::updateButtons() {
	this->nextBtn->update(this->mousePosWindow);
	if (this->nextBtn->isPressed())
	{
		this->endState();
	}
}

void GameIntro::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void GameIntro::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->title);
	target->draw(gamePlayText);
	target->draw(enemyText);
	target->draw(gamePlayText);
	target->draw(gamePlayText);
	target->draw(playerText);
	target->draw(enemyMelee);
	target->draw(enemyRanged);
	target->draw(enemyProj);
	target->draw(player);
	target->draw(playplayerProjer);
	
	this->nextBtn->render(*target);
}