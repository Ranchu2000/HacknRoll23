#ifndef STATE_h
#define STATE_h
#include "imports.h"


class State;

class StateData {
public:
	StateData() {};
	float gridSize;
	float mapSize;
	RenderWindow* window;
	std::stack<State*>* states;
};

class State {
protected:
	StateData* stateData;
	std::stack<State*>* states;
	RenderWindow* window;

	bool quit;
	bool paused;
	float gridSize;
	float mapSize;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Vector2i mousePosGrid;

	std::map<std::string, Texture> textures;
public:
	State(StateData* state_data);
	virtual ~State();

	const bool& getQuit() const;

	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions(View* view = NULL);
	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;
};
#endif