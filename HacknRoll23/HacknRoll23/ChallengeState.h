#ifndef CHALLENGESTATE_H
#define CHALLENGESTATE_H

#include "MainMenuState.h"
#include "imports.h"
#include "DEFINITIONS.h"

class ChallengeState :
	public State
{
private:
	Texture backgroundTexture;
	RectangleShape background;
	Font font;
	Text challenge;

	Sprite title;
	Texture titleTex;

	Sprite logo;
	Texture logoTex;

	gui::Button* acceptBtn;


	void initVariables();

	void initGui(); //textures, positioning, font

public:
	ChallengeState(StateData* state_data);
	~ChallengeState();
	void initFonts();
	void resetGui();
	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(RenderTarget& target);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);//draw stuff
};
#endif