#include "GameSounds.h"


GameSounds::GameSounds() {
	this->initVariables();
	this->loadETDtoBuffer();
	this->loadPTDtoBuffer();
	this->loadShootSoundtoBuffer();
}

void GameSounds::initVariables() {
	if (!this->startGameMusic.openFromFile(MAIN_MENU_MUSIC))
	{
		throw("ERROR::startGameMusic::COULD NOT LOAD MUSIC");
	}
	if (!this->gameOverMusic.openFromFile(GAME_OVER_MUSIC))
	{
		throw("ERROR::startGameMusic::COULD NOT LOAD MUSIC");
	}
	if (!this->gameStateMusic.openFromFile(GAME_STATE_MUSIC))
	{
		throw("ERROR::startGameMusic::COULD NOT LOAD MUSIC");
	}
	if (!this->VictoryMusic.openFromFile(VICTORY_MUSIC))
	{
		throw("ERROR::startGameMusic::COULD NOT LOAD MUSIC");
	}
}

GameSounds::~GameSounds() {}

void GameSounds::loadETDtoBuffer() {
	if (!this->enemybuffer.loadFromFile(ENEMY_TAKE_DMG_SOUND))
		throw("ERROR::enemy take damage::COULD NOT LOAD MUSIC");
	enemyTakeDamageSound.setBuffer(enemybuffer);
}

void GameSounds::loadPTDtoBuffer() {
	if (!this->playerbuffer.loadFromFile(PLAYER_TAKE_DMG_SOUND))
		throw("ERROR::player take damage::COULD NOT LOAD MUSIC");
	playerTakeDamageSound.setBuffer(playerbuffer);
}

void GameSounds::loadShootSoundtoBuffer() {
	if (!this->shootbuffer.loadFromFile(SHOOT_SOUND))
		throw("ERROR::shoot sound::COULD NOT LOAD MUSIC");
	shootSound.setBuffer(shootbuffer);
}