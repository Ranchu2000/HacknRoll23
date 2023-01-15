#include "BossProjectile.h"

BossProjectile::BossProjectile(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, sf::Texture& tex)
	: Projectiles(start, normDir, damage, health, tex)
{
}

BossProjectile::~BossProjectile() {}

void BossProjectile::move(const float& dt)
{
	this->sprite.setScale(2.f, 2.f);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.move(this->velocity * dt);
}
