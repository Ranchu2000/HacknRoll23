#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "imports.h"
#include "Player.h"

class GameState : public State
{
private:
	// Background
	Texture backgroundTexture;
	Sprite background;
	View view;

	// Text/GUI
	Font font;

	Texture pauseText;
	Sprite pauseButton;

	Text hp;
	Text hpText;
	RectangleShape hpMaxBar;
	RectangleShape hpCurBar;

	Text waveText;
	Text enemiesText;

	std::map<std::string, int> upgradeCur;

	// Player
	Player* player;
	Texture playerTex;
	float noDamageTimer;

	// Wave
	int waveNum;
	int spawnTimer;
	int spawnTimerMax;
	int enemiesLeft;
	int score;
	
	void initVariables();
	void initFonts();
	void initPlayer();
	void initGui();
	void resetGui();

public:
	GameState(StateData* state_data, std::map<std::string, int> upgradeCur, int waveNum);
	virtual ~GameState();

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayer(const float& dt);
	void updateView(const float& dt);
	void updateCollision(const float& dt);
	void updateButtons();
	void updateGameState(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);

};

#endif