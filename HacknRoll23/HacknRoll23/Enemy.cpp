#include "Enemy.h"

void Enemy::initVariables() {

}

void Enemy::initAnimations() {

}

Enemy::Enemy(Player& player) {
	this->initVariables();
	this->initAnimations();
}

Enemy::~Enemy() {

}

const bool Enemy::getDamageTimerDone() const{
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

const bool Enemy::getDespawnTimerDone() const {
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}

void Enemy::resetDamageTimer() {
	this->damageTimer.restart();
}

void Enemy::resetBurnTimer() {
	this->burnTimer.restart();
}

void Enemy::setTotalBurnDamage(int burnDamage) {
	this->totalBurnDamage = burnDamage;
}

void Enemy::loseHP(const int hp, Vector2f projectileDirection, const float& dt) {
	// to be implemented once entity class is up
}

const bool Enemy::isDead() const {
	// to be implemented once entity class is up
	return true;
}

const bool Enemy::isBurning() const {
	// to be implemented once entity class is up
	return true;
}

//const AttributeComponent* Enemy::getAttributeComp() const {
//	// to be implemented once entity class is up
//};

void Enemy::updateBurn() {
	// to be implemented once entity class is up
}
