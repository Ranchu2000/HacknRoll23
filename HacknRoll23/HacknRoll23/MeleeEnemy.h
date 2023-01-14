#pragma once

#include "imports.h"
#include "Enemy.h"
#include "AIFollow.h"

class MeleeEnemy: public Enemy
{
public: 
	MeleeEnemy(float x, float y, sf::Texture texture_sheet, Player& player);
	virtual ~MeleeEnemy();

	//Functions
	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
	void render(sf::RenderTarget& target);
	void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox);

private:
	void initVariables();
	void initAI();
	void initGUI();
	void initAnimations();

	sf::RectangleShape hpBar;
	AIFollow* follow;
};

