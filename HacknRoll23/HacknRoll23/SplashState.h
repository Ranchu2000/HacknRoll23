#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "imports.h"

class SplashState:
	public State
{
private:
	RectangleShape background;
	Texture logoTexture;
	Sprite logo;
	Sprite title;
	Texture titleTexture;
	float timeShown;

	void initVariables();
	void initGui();
public:
	SplashState(StateData* state_data);
	~SplashState();

	//Functions
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif
