#ifndef GAMEINTROSTATE_H
#define GAMEINTROSTATE_H

#include "MainMenuState.h"

class GameIntro :
	public State
{
private:
	RectangleShape background;
	Font font;
	Text title;

	Text gamePlayText;
	Text enemyText;
	Text playerText;

	Texture enemyTexture;
	Sprite enemy;

	Texture playerTexture;
	Sprite player;



	gui::Button* nextBtn;

	void initVariables();

	void initGui();

public:
	GameIntro(StateData* state_data);
	~GameIntro();
	void initFonts();
	void resetGui();
	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(RenderTarget& target);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif