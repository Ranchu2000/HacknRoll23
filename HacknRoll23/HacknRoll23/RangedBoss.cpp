#include "RangedBoss.h"


//Initializer functions
void RangedBoss::initVariables()
{
	this->clock.restart();
	this->attackInterval = 500.f;

}

void RangedBoss::initAI()
{
}

void RangedBoss::initGUI()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(60.f, 10.f));
}

void RangedBoss::initAnimations() {
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 1, 0, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 0, 3, 0, 64, 64);
	this->animationComponent->addAnimation("ATTACK_UP", 11.f, 0, 4, 1, 4, 64, 64);
	this->animationComponent->addAnimation("ATTACK_DOWN", 11.f, 0, 5, 1, 5, 64, 64);
	this->animationComponent->addAnimation("ATTACK_LEFT", 11.f, 0, 6, 1, 6, 64, 64);
	this->animationComponent->addAnimation("ATTACK_RIGHT", 11.f, 0, 7, 1, 7, 64, 64);

}

//Constructors / Destructors
RangedBoss::RangedBoss(float x, float y, sf::Texture& texture_sheet, Player& player)
	: Enemy(player)
{
	this->initVariables();
	this->initGUI();
	this->createAnimation(texture_sheet);
	this->createHitbox(this->sprite, 80.f, 0.f, 160.f, 160.f);
	this->createMovement(250.f, 1000.f, 400.f);
	this->createAttribute(1, 50, 5);

	//this->generateAttributes(this->attributeComponent->level);						

	this->setPosition(x, y);
	this->initAnimations();

	this->follow = new AIRanged(player, *this);
}


RangedBoss::~RangedBoss()
{
	delete this->follow;
}

void RangedBoss::updateAnimation(const float& dt)
{
	if (this->isAttacking)
	{
		if (this->follow->getCardinalDirection() == EAST)
			this->animationComponent->play("ATTACK_RIGHT", dt);
		else if (this->follow->getCardinalDirection() == WEST)
			this->animationComponent->play("ATTACK_LEFT", dt);
		else if (this->follow->getCardinalDirection() == NORTH)
			this->animationComponent->play("ATTACK_UP", dt);
		else if (this->follow->getCardinalDirection() == SOUTH)
			this->animationComponent->play("ATTACK_DOWN", dt);
	}
	else if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	this->sprite.setScale(2.5f, 2.5f);
	if (this->isBurning())
	{
		this->sprite.setColor(sf::Color::Red);
	}
	else
		this->sprite.setColor(sf::Color::White);
}

void RangedBoss::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	Enemy::update(dt, mouse_pos_view, view);

	this->movementComponent->update(dt);


	this->hpBar.setSize(Vector2f(10.f * this->attributeComponent->getCurHealth(), 10.f));
	this->hpBar.setPosition(Vector2f(this->sprite.getPosition().x + 32.f - this->hpBar.getGlobalBounds().width / 2, this->sprite.getPosition().y));

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->follow->update(dt);
	this->attack();
}
void RangedBoss::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitboxComponent->render(target);
	target.draw(this->hpBar);
}


void RangedBoss::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}

	target.draw(this->hpBar);

	if (show_hitbox)
		this->hitboxComponent->render(target);
}

void RangedBoss::attack() {
	if (!this->follow->inRange())
	{
		isAttacking = false;
	}
	if (this->follow->inRange()) {
		isAttacking = true;
	}
}