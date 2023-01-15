#pragma once

#include "imports.h"
#include "DEFINITIONS.h"


class GameSounds
{
public:
	sf::Music startGameMusic;
	sf::Music gameOverMusic;
	sf::Music gameStateMusic;
	sf::Music VictoryMusic;

	sf::SoundBuffer enemybuffer;
	sf::SoundBuffer playerbuffer;
	sf::SoundBuffer shootbuffer;

	sf::Sound enemyTakeDamageSound;
	sf::Sound playerTakeDamageSound;
	sf::Sound shootSound;


	GameSounds();
	~GameSounds();

	void initVariables();

	void loadETDtoBuffer();

	void loadPTDtoBuffer();

	void loadShootSoundtoBuffer();
};

