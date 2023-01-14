#include "Entity.h"
#include "DEFINITIONS.h"

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
}

void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
}

//Compoenent functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createAttribute(const int level, const int hpMax, const int damage)
{
	this->attributeComponent = new AttributeComponent(level, hpMax, damage);
}

void Entity::createMovement(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimation(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}


//Accessors
HitboxComponent* Entity::getHitboxComponent()
{
	return this->hitboxComponent;
}


MovementComponent* Entity::getMovementComponent()
{
	return this->movementComponent;
}

AnimationComponent* Entity::getAnimationComponent()
{
	return this->animationComponent;
}

AttributeComponent* Entity::getAttributeComponent()
{
	return this->attributeComponent;
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2f& Entity::getSpritePosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition() + sf::Vector2f(this->hitboxComponent->getGlobalBounds().width / 2.f, this->hitboxComponent->getGlobalBounds().height / 2.f);

	return
		this->sprite.getPosition() + sf::Vector2f(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
}

const sf::Vector2f Entity::getSpriteCenter() const
{
	return this->sprite.getPosition() + sf::Vector2f(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI, static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI);

	return sf::Vector2i(static_cast<int>(this->sprite.getPosition().x) / gridSizeI, static_cast<int>(this->sprite.getPosition().y) / gridSizeI);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

sf::Sprite Entity::getSprite()
{
	return this->sprite;
}

//Mutator
void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}


void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt); //Sets velocity
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();

}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

//Calculations
void Entity::checkCollision(const float& dt)
{
	// Left
	if (this->getPosition().x < GRIDSIZE)
	{
		this->setPosition(GRIDSIZE + 1, this->getPosition().y);
	}
	// Right
	else if (this->getPosition().x + this->getGlobalBounds().width > ((MAPSIZE)*GRIDSIZE) - (GRIDSIZE))
	{
		this->setPosition(((MAPSIZE)*GRIDSIZE) - (GRIDSIZE + 1) - this->getGlobalBounds().width, this->getPosition().y);
	}
	// Top
	if (this->getPosition().y < GRIDSIZE)
	{
		this->setPosition(this->getPosition().x, GRIDSIZE + 1);
	}
	// Bottom
	else if (this->getPosition().y + this->getGlobalBounds().height > ((MAPSIZE)*GRIDSIZE) - (GRIDSIZE))
	{
		this->setPosition(this->getPosition().x, ((MAPSIZE)*GRIDSIZE) - (GRIDSIZE + 1) - this->getGlobalBounds().height);
	}
}

float Entity::getDistance(const Entity& entity) const
{
	return sqrt(pow(this->getCenter().x - entity.getCenter().x, 2) + pow(this->getCenter().y - entity.getCenter().y, 2));
}

float Entity::getSpriteDistance(const Entity& entity) const
{
	return sqrt(pow(this->getSpriteCenter().x - entity.getSpriteCenter().x, 2) + pow(this->getSpriteCenter().y - entity.getSpriteCenter().y, 2));
}