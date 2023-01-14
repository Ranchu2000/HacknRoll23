#ifndef projectiles_H
#define projectiles_H

#include "imports.h"

class Projectiles
{

protected:
	sf::Sprite sprite;
	sf::Vector2f start;
	sf::Vector2f normDir;
	float speed;
	sf::Vector2f velocity;
	int damage;
	int health;
	bool piercingEntity; //Check if piercing arrow is still in enemy to avoid dealing extra damage



public:
	//constructor and destructor
	Projectiles(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, sf::Texture& tex);
	~Projectiles();

	//Accessors
	sf::Sprite getSprite();
	const sf::Vector2f getNormDir();
	const float getSpeed();
	const sf::Vector2f getVelocity();
	const int getDamage();
	const bool isInEntity();

	//Mutators
	int reduceHealth();
	void setPiercingEntity(bool status);

	//Functions
	virtual void move(const float& dt);
	void render(sf::RenderTarget& target);

};

#endif

