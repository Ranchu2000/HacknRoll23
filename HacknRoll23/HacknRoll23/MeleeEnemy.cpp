#include "MeleeEnemy.h"

void MeleeEnemy::initVariables()
{

};

void MeleeEnemy::initAI()
{

};

void MeleeEnemy::initGUI()
{
	this->hpBar.setFillColor(Color::Red);
	this->hpBar.setSize(Vector2f(60.f, 10.f));
};

void MeleeEnemy::initAnimations()
{
	//this->createAnimation(texture_sheet)
};

MeleeEnemy::MeleeEnemy(float x, float y, sf::Texture texture_sheet, Player& player)
	: Enemy(player)
{
	std::srand(time(0));
	this->initVariables();
	this->initGUI();
	this->initAnimations();
	//this->createHitbox(this->sprite, 0.f, 0.f, 64.f, 64.f);
	//this->createMovement((rand() % (51)) + 400.f, 500.f, 200.f);
	//this->createAttribute(1, 5, 1);
	//this->setPosition(x, y);

	this->follow = new AIFollow(player, *this);
};

MeleeEnemy::~MeleeEnemy()
{
	delete this->follow;
};

//Functions
void MeleeEnemy::updateAnimation(const float& dt)
{
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

	//TODO: Add burning animation logic as well
};
void MeleeEnemy::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	this->movementComponent->update(dt);

	this->hpBar.setSize(Vector2f(10.f * this->attributeComponent->getCurHealth(), 10.f));
	this->hpBar.setPosition(Vector2f(this->sprite.getPosition().x + 32.f - this->hpBar.getGlobalBounds().width / 2, this->sprite.getPosition().y - 10.f));

	this->updateAnimation(dt);
	this->hitboxComponent->update();

	this->follow->update(dt);
};

void MeleeEnemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitboxComponent->render(target);
	target.draw(this->hpBar);
};

void MeleeEnemy::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
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
};

