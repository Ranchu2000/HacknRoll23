#include "AIRanged.h"

AIRanged::AIRanged(Player& self, Enemy& entity) :self(self), entity(entity) {}

AIRanged::~AIRanged() {}

void AIRanged::update(const float& dt)
{
	sf::Vector2f moveVec;
	moveVec.x = -(entity.getPosition().x - self.getPosition().x);
	moveVec.y = -(entity.getPosition().y - self.getPosition().y);

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));
	this->direction = moveVec;
	moveVec /= vecLength;

	if (std::abs(vecLength) > 650.f)
		entity.move(moveVec.x, moveVec.y, dt); //run towards
	else if (std::abs(vecLength) < 630.f) {
		entity.move(-moveVec.x, -moveVec.y, dt); //run away
	}
}

bool AIRanged::inRange() {
	float vecLength = sqrt(pow(this->direction.x, 2) + pow(this->direction.y, 2));
	if (std::abs(vecLength) < 650.f) {
		return true;
	}
	return false;
}

CARDINAL_DIRECTION AIRanged::getCardinalDirection() {
	CARDINAL_DIRECTION facing{ LOST };
	float degree = -atan2(this->direction.y, this->direction.x) * 180 / PI;
	if (degree > 45 && degree < 135)
		facing = NORTH;
	if (degree > 135)
		facing = WEST;
	if (degree < -135)
		facing = WEST;
	if (degree > -45 && degree < 45)
		facing = EAST;
	if (degree > -135 && degree < -45)
		facing = SOUTH;

	return facing;
};