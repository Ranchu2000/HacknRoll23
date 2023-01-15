#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "imports.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"


class GameOverState :
	public State
{
private:
	Font font;
	RectangleShape background;

	Text title;
	Text challenge;
	Text text;
	
	Texture lossText;
	Sprite lossIcon;


	Texture retryText;
	Sprite retryBtn;

	Texture homeText;
	Sprite homeBtn;

	int waves = 0;
	int enemies = 0;
	std::map<std::string, int> initialStats;

	void initFont();
	void initVariables();
	void initGui();
public:
	GameOverState(StateData* state_data, int score, int waveNum);
	~GameOverState();

	//Functions
	void update(const float& dt);
	void updateInput(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif
