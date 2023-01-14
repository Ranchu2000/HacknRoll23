#pragma once

#include "imports.h"
#include "Enemy.h"
#include "Player.h"

class AIFollow
{
public:
	AIFollow(Player& player, Enemy& enemy);
	~AIFollow();

	void update(const float& dt);

protected:
	Player& player;
	Enemy& enemy;
};

