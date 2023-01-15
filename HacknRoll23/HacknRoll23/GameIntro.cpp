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

	this->border.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width*0.005f),
			static_cast<float>(vm.height*0.83f)
		)
	);
	this->border.setFillColor(Color(RED_COLOR));
	this->border.setPosition(gui::p2pX(50.0f, vm), gui::p2pY(15.0f, vm));


	
	this->title.setFont(this->font);
	this->title.setCharacterSize(gui::calcCharSize(vm, 30));
	this->title.setFillColor(Color(RED_COLOR));
	this->title.setStyle(Text::Bold);
	this->title.setString("Game Introduction");
	this->title.setPosition(gui::p2pX(50.0f, vm)- this->title.getGlobalBounds().width/2, gui::p2pY(5.f, vm));

	this->gamePlayText.setFont(this->font);
	this->gamePlayText.setCharacterSize(gui::calcCharSize(vm, 80));
	this->gamePlayText.setFillColor(Color(RED_COLOR));
	this->gamePlayText.setStyle(Text::Regular);
	this->gamePlayText.setString("Timmy has to clear 5 waves of enemies to win.\nAll enemies must be cleared in order to\nproceed. Each wave will get increasingly\ndifficult but fret not, player upgrades awaits\nduring intermission state after each wave.");
	this->gamePlayText.setPosition(gui::p2pX(1.0f, vm), gui::p2pY(18.f, vm));

	this->playerText.setFont(this->font);
	this->playerText.setCharacterSize(gui::calcCharSize(vm, 80));
	this->playerText.setFillColor(Color(RED_COLOR));
	this->playerText.setStyle(Text::Regular);
	this->playerText.setString("T I M M Y\n\nTo face his dream firms, Timmy is\narmed with many resume copies\nwhich will be his ammunition.\nBoth Timmy's avatar and resume\nstats can be upgraded during the\nintermission.");
	this->playerText.setPosition(gui::p2pX(14.0f, vm), gui::p2pY(50.f, vm));

	this->playerTexture.loadFromFile(PLAYER_FILEPATH);
	this->player.setTexture(playerTexture);
	this->player.scale(1.75f, 1.75f);
	this->player.setPosition(gui::p2pX(1.75f, vm), gui::p2pY(47.5f, vm));

	this->playerProjTexture.loadFromFile(PLAYER_PROJ_FILEPATH);
	this->playerProj.setTexture(playerProjTexture);
	this->playerProj.scale(1.25f, 1.25f);
	this->playerProj.setPosition(gui::p2pX(2.55f, vm), gui::p2pY(70.f, vm));


	this->enemyText.setFont(this->font);
	this->enemyText.setCharacterSize(gui::calcCharSize(vm, 80));
	this->enemyText.setFillColor(Color(RED_COLOR));
	this->enemyText.setStyle(Text::Regular);
	this->enemyText.setString("There are 2 types of firms Timmy will\nencounter, Melee and Ranged Enemies.");
	this->enemyText.setPosition(gui::p2pX(52.0f, vm), gui::p2pY(18.f, vm));

	this->meleeEnemyText.setFont(this->font);
	this->meleeEnemyText.setCharacterSize(gui::calcCharSize(vm, 80));
	this->meleeEnemyText.setFillColor(Color(RED_COLOR));
	this->meleeEnemyText.setStyle(Text::Regular);
	this->meleeEnemyText.setString("C I T A D E L\nPreferred mode of attack: Melee");
	this->meleeEnemyText.setPosition(gui::p2pX(52.0f, vm), gui::p2pY(35.f, vm));


	this->rangedEnemyText.setFont(this->font);
	this->rangedEnemyText.setCharacterSize(gui::calcCharSize(vm, 80));
	this->rangedEnemyText.setFillColor(Color(RED_COLOR));
	this->rangedEnemyText.setStyle(Text::Regular);
	this->rangedEnemyText.setString("T I K T O K\nPreferred mode of attack: Ranged\nProjectile: pure disapproval");
	this->rangedEnemyText.setPosition(gui::p2pX(52.0f, vm), gui::p2pY(60.f, vm));

	this->enemyMeleeTexture.loadFromFile(MELEE_ENEMY_FILEPATH);
	this->enemyMelee.setTexture(enemyMeleeTexture);
	this->enemyMelee.scale(1.75f, 1.75f);
	this->enemyMelee.setPosition(gui::p2pX(87.5f, vm), gui::p2pY(30.f, vm));

	this->enemyRangedTexture.loadFromFile(RANGED_ENEMY_FILEPATH);
	this->enemyRanged.setTexture(enemyRangedTexture);	
	this->enemyRanged.scale(1.75f, 1.75f);
	this->enemyRanged.setPosition(gui::p2pX(87.5f, vm), gui::p2pY(52.f, vm));

	this->enemyProjTexture.loadFromFile(ENEMY_PROJ_FILEPATH);
	this->enemyProj.setTexture(enemyProjTexture);
	this->enemyProj.scale(1.25f, 1.25f);
	this->enemyProj.setPosition(gui::p2pX(87.5f, vm), gui::p2pY(67.5f, vm));
	
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
	target->draw(this->border);
	target->draw(this->gamePlayText);
	
	target->draw(this->gamePlayText);
	target->draw(this->gamePlayText);
	target->draw(this->playerText);
	target->draw(this->player);
	target->draw(this->playerProj);
	target->draw(this->enemyText);
	target->draw(this->meleeEnemyText);
	target->draw(this->enemyMelee);
	target->draw(this->rangedEnemyText);
	target->draw(this->enemyRanged);
	target->draw(this->enemyProj);
	target->draw(this->enemyMelee);
	target->draw(this->enemyRanged);
	target->draw(this->enemyProj);
	target->draw(this->player);
	target->draw(this->playerProj);
	
	this->nextBtn->render(*target);
}