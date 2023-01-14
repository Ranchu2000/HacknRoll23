#include "GameState.h"
#include "imports.h"
#include "DEFINITIONS.h"

void GameState::initVariables()
{
	this->waveNum += 1;
	this->score = 0;
}

void GameState::initFonts()
{
}

void GameState::initPlayer()
{
}

void GameState::initGui()
{
}

void GameState::resetGui()
{
}

GameState::GameState(StateData* state_data, int waveNum) : State(state_data), waveNum(waveNum)
{
	this->initVariables();
	this->initFonts();
	this->initGui();
	this->initPlayer();
}

void GameState::updateInput(const float& dt)
{
}

void GameState::updatePlayerInput(const float& dt)
{
}

void GameState::updatePlayer(const float& dt)
{
}

void GameState::updateCollision(const float& dt)
{
}

void GameState::updateButtons(const float& dt)
{
}

void GameState::update(const float& dt)
{
}

void GameState::renderButtons(RenderTarget* target)
{
}

void GameState::render(RenderTarget* target)
{
}
