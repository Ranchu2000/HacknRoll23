#include "AttributeComponent.h"
#include "DEFINITIONS.h"


//Constuctors and destructor
AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
}

AttributeComponent::AttributeComponent(int level, int hpMax, int damage)
{
	this->level = level;
	this->hpMax = hpMax;
	this->hp = hpMax;
	this->damageMax = damage;
	this->damageMin = damage;
}

AttributeComponent::~AttributeComponent(){}

//Accessors
const bool AttributeComponent::isDead() const
{
	return this->hp <= 0;
}

int AttributeComponent::getCurHealth() {
	return this->hp;
}

int AttributeComponent::getMaxHealth() {
	return this->hpMax;
}

//Mutators
void AttributeComponent::resetStats()
{
	this->hp = this->hpMax;
}

void AttributeComponent::LevelUp()
{
	++this->level;
}

void AttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

void AttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void AttributeComponent::increaseDamage(int levels) {
	this->damageMax += levels * PLAYER_UPGRADE_DAMAGE;
	this->damageMin += levels * PLAYER_UPGRADE_DAMAGE;
}

void AttributeComponent::increaseHealth(int levels) {
	this->hpMax += levels * PLAYER_UPGRADE_HEALTH;
	this->hp = hpMax;
}