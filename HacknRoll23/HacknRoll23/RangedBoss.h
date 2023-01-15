#pragma once
#include "AIRanged.h"
#include "Enemy.h"


class RangedBoss :
	public Enemy
{
private:
	void initVariables();
	void initAI();
	void initGUI();
	void initAnimations();


	sf::RectangleShape hpBar;
	AIRanged* follow;

public:
	bool isAttacking = false;
	Clock clock;
	float attackInterval; //change this in initVariables

	RangedBoss(float x, float y, sf::Texture& texture_sheet, Player& player);
	virtual ~RangedBoss();

	//Functions
	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
	void render(sf::RenderTarget& target);
	void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox);
	void attack();
};

