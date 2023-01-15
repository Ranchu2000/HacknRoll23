#pragma once
#include "Projectiles.h"
class BossProjectile :
    public Projectiles
{
public:
    BossProjectile(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, sf::Texture& tex);
    ~BossProjectile();

    void move(const float& dt) override;
};

