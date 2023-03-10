#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameOverState.h"
#include"VictoryState.h"
#include "imports.h"
#include "IntermissionState.h"
#include "GameSounds.h"


class MainMenuState:
	public State
{
private:
	Font font;
	Text Title;

	Texture logoTexture;
	Sprite logo;

	RectangleShape background;
	RectangleShape instructionBackground;

	Text how2play;
	Text how2playInstructions;
	Text how2win;
	Text how2winInstruction;

	Texture mouseIconTexture;
	Sprite mouseIcon;
	Texture keyboardIconTexture;
	Sprite keyboardIcon;

	std::map<std::string, gui::Button*> buttons;
	RectangleShape btnBG1;
	RectangleShape btnBG2;

	std::map<std::string, int> initialStats;
	int initialWave;

	GameSounds* gamesound;

	void initVariables();
	void initFont();
	void initGui();
	void resetGui();
public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons(); 
	void update(const float& dt);
	void renderButtons(RenderTarget& target); 
	void render(RenderTarget* target = NULL);
};

#endif
