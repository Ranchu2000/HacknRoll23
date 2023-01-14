#include "AIFollow.h"

AIFollow::AIFollow(Player& player, Enemy& enemy): player(player), enemy(enemy) {}

AIFollow::~AIFollow(){}

void AIFollow::update(const float& dt)
{
	sf::Vector2f moveVec;

	moveVec.x = player.getCenter().x - enemy.getCenter().x;
	moveVec.y = player.getCenter().y - enemy.getCenter().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if ((player.getCenter().x != enemy.getCenter().x) && std::abs(vecLength) < 2000.f)
		enemy.move(moveVec.x, moveVec.y, dt);
}
