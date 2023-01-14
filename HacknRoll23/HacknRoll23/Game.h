#ifndef GAME_H
#define GAME_H
#include "imports.h"
#include "State.h"
#include "MainMenuState.h"
#include "SplashState.h"

class Game
{
public:
	Game();
	~Game();

	void updateDt();
	void updateSFMLEvents();

	void run();
	void update();
	void render();

private:
	StateData stateData;
	Event sfEvent;
	RenderWindow* window;
	
	Clock dtClock;
	float dt;

	std::stack<State*> states;

	float gridSize;
	float mapSize;


	void initVariables();
	void initWindow();
	void initStateData();
	void initState();
};
#endif
