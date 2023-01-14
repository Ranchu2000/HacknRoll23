#pragma once

#include "imports.h"
#include "Enemy.h"

class AIFollow
{
public:
	AIFollow(Player& player, Enemy& Enemy);
	~AIFollow();

	void update(const float& dt);

protected:
	Player& player;
	Enemy& enemy;
};

