#pragma once
#include "Projectiles.h"
class EnemyProjectile :
    public Projectiles
{
public:
    EnemyProjectile(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, sf::Texture& tex);
    ~EnemyProjectile();

    void move(const float& dt) override;
};

