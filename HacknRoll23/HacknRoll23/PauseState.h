#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "imports.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "GameState.h"

class PauseState:public State
{
private:
	Font font;
	RectangleShape background;
	RectangleShape backgroundScreen;

	Text text;
	Texture resumeText;
	Sprite resumeButton;

	Texture homeText;
	Sprite homeButton;

	void initFonts();
	void initVariables();
	void initGui();
public:
	PauseState(StateData* state_data);
	~PauseState();

	//Functions
	void update(const float& dt);
	void updateInput(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif