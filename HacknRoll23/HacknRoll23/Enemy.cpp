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
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);

		Vector2f initialPosition = this->getPosition();

		for (int i = 0; i < 3; i++) { //knock back from projectile hit
			this->move(projectileDirection.x * 20.f, projectileDirection.y * 20.f, dt);
		}
	}
}

const bool Enemy::isDead() const {
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}

	return false;
}

//const bool Enemy::isBurning() const {
//	// to be implemented once skiils class up
//}

const AttributeComponent* Enemy::getAttributeComp() const {
	// to be implemented once skills class up
	return this->attributeComponent;
};

void Enemy::updateBurn() {
	// to be implemented once skills class up
}
