#include "EnemyProjectile.h"

EnemyProjectile::EnemyProjectile(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, sf::Texture& tex)
	: Projectiles(start, normDir, damage, health, tex)
{
}

EnemyProjectile::~EnemyProjectile() {}

void EnemyProjectile::move(const float& dt)
{
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.move(this->velocity * dt);
}
