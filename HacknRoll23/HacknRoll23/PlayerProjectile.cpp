#include "PlayerProjectile.h"
#include "DEFINITIONS.h"


//Constructor and destructor
PlayerProjectile::PlayerProjectile(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, sf::Texture& tex) : Projectiles(start, normDir, damage, health, tex)
{
	this->burnLevel = 0;
}
PlayerProjectile::PlayerProjectile(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, int burnLevel, sf::Texture& tex) : Projectiles(start, normDir, damage, health, tex)
{
	this->burnLevel = burnLevel;
	this->sprite.setColor(sf::Color::Red);
}
PlayerProjectile::~PlayerProjectile() {}

//Accessor
const int PlayerProjectile::getBurnLevel()
{
	return this->burnLevel;
}