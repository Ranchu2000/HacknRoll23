#include "State.h"

State::State(StateData* state_data) {
	this->stateData = state_data;
	this->window = state_data->window;
	this->states = state_data->states;
	this->quit = false;
	this->paused = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
	this->gridSize = state_data->gridSize;
	this->mapSize = state_data->mapSize;
}

const bool& State::getQuit()const {
	return this->quit;
}

const bool State::getKeyTIme()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions(sf::View* view)
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	if (view)
		this->window->setView(*view);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid =
		sf::Vector2i(
			static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
			static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
		);
	this->window->setView(this->window->getDefaultView());
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 100.f * dt;
}