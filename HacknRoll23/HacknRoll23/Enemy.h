#pragma once

#include "imports.h"
#include "Entity.h"

class AIFollow;
class Player;
class AttributeComponent;

class Enemy: public Entity
{
protected:
	// Enemy variables
	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;
	sf::Clock despawnTimer;
	sf::Int32 despawnTimerMax;
	sf::Clock burnTimer;
	sf::Int32 burnTimerMax;
	int totalBurnDamage;

	//Initializer functions
	virtual void initVariables();
	virtual void initAnimations();


public:
	Enemy(Player& player);
	~Enemy();
	
	//Accessors
	const bool getDamageTimerDone() const;
	const bool getDespawnTimerDone() const;


	//Modifiers
	void resetDamageTimer();
	void resetBurnTimer();
	void setTotalBurnDamage(int burnDamage);

	//Functions

	virtual void loseHP(const int hp, Vector2f projectileDirection, const float& dt);
	virtual const bool isDead() const;
	const bool isBurning() const;

	/*virtual const AttributeComponent* getAttributeComp() const;*/

	virtual void updateAnimation(const float& dt) = 0;
	void updateBurn();

	virtual void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;

private:
};

