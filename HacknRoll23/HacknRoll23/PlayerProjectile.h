#ifndef playerprojectile_H
#define playerprojectile_H

#include "Projectiles.h"

class PlayerProjectile : public Projectiles
{
private:
    int burnLevel;
public:
    //Constructor and destructor
    PlayerProjectile(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, sf::Texture& tex);
    PlayerProjectile(sf::Vector2f start, sf::Vector2f normDir, int damage, int health, int burnLevel, sf::Texture& tex);
    ~PlayerProjectile();

    //Accessor
    const int getBurnLevel();
};

#endif