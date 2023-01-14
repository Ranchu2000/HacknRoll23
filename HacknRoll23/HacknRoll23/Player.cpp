#include "Player.h"
#include "DEFINITIONS.h"

void Player::initVariables()
{
	this->initAttack = false;
	this->attacking = false;
	this->skillList = new SkillList();
	this->damageInterval = 0.7f;
}

void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 4, 3, 4, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 0, 3, 0, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 11.f, 0, 1, 3, 1, 64, 64);
}

Player::Player(float x, float y, sf::Texture& texture_sheet, std::map<std::string, int> upgradeCur) :
	upgradeCur(upgradeCur)
{
	this->initVariables();

	this->createAnimation(texture_sheet);
	this->initAnimations();

	this->createHitbox(this->sprite, 0.f, 0.f, 64.f, 64.f);

	this->damageInterval -= this->upgradeCur["Firing"] * 0.1f;

	this->skillList->increaseBurnLevel(this->upgradeCur["Burn"]);
	this->skillList->increasePierceLevel(this->upgradeCur["Pierce"]);


	this->createAttribute(1, PLAYER_INITIAL_HEALTH, PLAYER_INITIAL_DAMAGE);
	this->attributeComponent->increaseHealth(this->upgradeCur["Health"]);
	this->attributeComponent->increaseDamage(this->upgradeCur["Attack"]);

	this->createMovement(PLAYER_INITIAL_SPEED, 1400.f, 1000.f);
	this->movementComponent->increaseMaxVelocity(this->upgradeCur["Speed"]);

	this->setPosition(x, y);
}

Player::~Player()
{

}

//Accessors
const bool& Player::getInitAttack() const
{
	return this->initAttack;
}

const float Player::getDamageTimer()
{
	return this->damageTimer.getElapsedTime().asSeconds();
}

const float Player::getDamageInterval()
{
	return this->damageInterval;
}

const int Player::getDamage()
{
	return this->attributeComponent->damageMin;
}

SkillList* Player::getSkillList()
{
	return this->skillList;
}

//Mutators 
void Player::resetAttackState()
{
	this->attacking = false;
	this->initAttack = false;
}

void Player::setDamageInterval(int newDamageInterval)
{
	this->damageInterval = newDamageInterval;
}

void Player::resetDamageTimer()
{
	this->damageTimer.restart();
}

void Player::setAttacking(const bool& attacking)
{
	this->attacking = attacking;
}


//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}


void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
	}
	if (this->movementComponent->getState(IDLE))
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
}

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//this->hitboxComponent->render(target);
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
	}
	else
	{
		target.draw(this->sprite);
	}

	if (show_hitbox)
		this->hitboxComponent->render(target);
}