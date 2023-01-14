#include "Projectiles.h"

Projectiles::Projectiles(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, sf::Texture& tex)
{
	this->start = start;
	this->normDir = normDir;
	this->damage = damage;
	this->health = health;
	this->speed = 1500.f;
	this->velocity = this->normDir * this->speed;
	this->sprite.setTexture(tex);
	this->sprite.setScale(0.7f, 0.7f);
	this->sprite.setPosition(start);
	this->piercingEntity = false;
}

Projectiles::~Projectiles() {}



sf::Sprite Projectiles::getSprite()
{
	return this->sprite;
}
const sf::Vector2f Projectiles::getNormDir()
{
	return this->normDir;
}
const float Projectiles::getSpeed()
{
	return this->speed;
}
const sf::Vector2f Projectiles::getVelocity()
{
	return this->velocity;
}
const int Projectiles::getDamage()
{
	return this->damage;
}
const bool Projectiles::isInEntity()
{
	return this->piercingEntity;
}


int Projectiles::reduceHealth()
{
	this->health--;
	return this->health;
}
void Projectiles::setPiercingEntity(bool status)
{
	this->piercingEntity = status;
}

void Projectiles::move(const float& dt)
{
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.rotate(180.f * dt);
	this->sprite.move(this->velocity * dt);
}

void Projectiles::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}