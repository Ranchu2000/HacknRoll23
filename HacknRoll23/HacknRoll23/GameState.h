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
	int score;
	
	void initVariables();
	void initFonts();
	void initPlayer();
	void initGui();
	void resetGui();

public:
	GameState(StateData* state_data, int waveNum);
	virtual ~GameState();

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayer(const float& dt);
	void updateView(const float& dt);
	void updateCollision(const float& dt);
	void updateButtons(const float& dt);
	void update(const float& dt);
	void renderButtons(RenderTarget* target);
	void render(RenderTarget* target = NULL);

};

#endif