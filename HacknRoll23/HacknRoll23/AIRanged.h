#pragma once
#include "Enemy.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <math.h>

#define PI 3.14159265

enum CARDINAL_DIRECTION { LOST = 0, NORTH = 1, SOUTH = 2, EAST = 3, WEST = 4 };

class AIRanged {
public:
	AIRanged(Player& self, Enemy& entity);
	~AIRanged();

	void update(const float& dt);
	bool inRange();
	CARDINAL_DIRECTION getCardinalDirection();


protected:
	Player& self;
	Enemy& entity;
	Vector2f direction;
};