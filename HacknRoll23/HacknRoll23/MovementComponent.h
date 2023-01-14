#ifndef movementcomponent_H
#define movementcomponent_H

#include "imports.h"


enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
	sf::Sprite& sprite;
	float maxVelocity;
	float acceleration;
	float deceleration;
	sf::Vector2f velocity;


public:
	//Constructors and destructor
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	//Mutators 
	void increaseMaxVelocity(int levels = 1);
	void setMaxVelocity(float velocity);

	//Functions
	const bool getState(const short unsigned state) const;
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};

#endif

