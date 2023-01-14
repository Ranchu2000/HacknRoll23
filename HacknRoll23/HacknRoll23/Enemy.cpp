#include "Enemy.h"

void Enemy::initVariables() {
	this->damageTimerMax = 1000;
	this->despawnTimerMax = 1000;
	this->burnTimerMax = 1000;
}

void Enemy::initAnimations() {
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 1, 0, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 0, 3, 0, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 11.f, 0, 1, 3, 1, 64, 64);
}

Enemy::Enemy(Player& player) {
	this->initVariables();
	//this->initAnimations();
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

const bool Enemy::isBurning() const {
	return this->totalBurnDamage > 0;
}

const AttributeComponent* Enemy::getAttributeComp() const {
	if (this->attributeComponent)
		return this->attributeComponent;
	else
	{
		std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INITIALIZED" << "\n";
		return nullptr;
	}
};

void Enemy::updateBurn() {
	if (this->totalBurnDamage > 0 && this->burnTimer.getElapsedTime().asMilliseconds() >= this->burnTimerMax)
	{
		this->attributeComponent->loseHP();
		this->burnTimer.restart();
		this->totalBurnDamage--;
	}
}

void Enemy::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	if (vectorDistance(this->getPosition(), view.getCenter()) < 1500.f)
		this->despawnTimer.restart();
}