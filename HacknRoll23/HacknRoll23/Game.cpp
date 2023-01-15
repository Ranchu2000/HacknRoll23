#include "Game.h"
#include "DEFINITIONS.h"

void Game::initVariables() {
	this->window = NULL;
	this->dt =0.0f;
	this->gridSize = GRIDSIZE;
	this->mapSize = MAPSIZE;
}

void Game::initWindow() {
	ContextSettings settings;
	settings.antialiasingLevel = 0;
	this->window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE, Style::Default);
	this->window->setFramerateLimit(FRAME_LIMIT);
	this->window->setVerticalSyncEnabled(VERTICAL_SYNC);
}

void Game::initStateData() {
	this->stateData.window = this->window;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
	this->stateData.mapSize = this->mapSize;
}
void Game::initState() {
	//push states one by one
	this->states.push(new MainMenuState(&this->stateData));
	this->states.push(new GameIntro(&this->stateData));
	this->states.push(new ChallengeState(&this->stateData));
	this->states.push(new SplashState(&this->stateData));
}

Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initStateData();
	this->initState();
}

Game::~Game() {
	delete this->window;
	//states emptying
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::updateDt() {
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents() {
	while (this->window->pollEvent(this->sfEvent)) {
		if (this->sfEvent.type == Event::Closed)
			this->window->close();
	}
}

void Game::update() {
	this->updateSFMLEvents();
	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);
			if (this->states.top()->getQuit()) //handles states exiting
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else
		this->window->close();
}

void Game::render() {
	this->window->clear();
	if (!this->states.empty()){
		
		this->states.top()->render();
	}
		
	this->window->display();
}

void Game::run() {
	while (this->window->isOpen()) {
		this->updateDt();
		this->update();
		this->render();
	}
}