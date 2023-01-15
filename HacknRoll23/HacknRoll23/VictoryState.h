#ifndef VICTORYSTATE_H
#define VICTORYSTATE_H

#include "imports.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "GameSounds.h"


class VictoryState :
	public State
{
private:
	Font font;
	RectangleShape background;

	Text title;
	Text prizeInstructions;
	Text text;

	Texture prizeTexture;
	RectangleShape prize;

	Texture wonText;
	Sprite wonIcon;

	Texture homeText;
	Sprite homeBtn;

	GameSounds* gamesounds;

	void initFont();
	void initVariables();
	void initGui();
public:
	VictoryState(StateData* state_data);
	~VictoryState();

	//Functions
	void update(const float& dt);
	void updateInput(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif
