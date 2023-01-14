#ifndef player_h
#define player_h

#include "SkillList.h"
#include "Entity.h"

class Player : public Entity
{

private:

    bool initAttack;
    bool attacking;

    std::map<std::string, int> upgradeCur; //player's upgraded stats

    SkillList* skillList; //Check player attributes and skillList when attacking, passed by ref 

    sf::Clock damageTimer;
    float damageInterval;

    //Initialisation«
    void initVariables();
    void initAnimations();


public:
    Player(float x, float y, sf::Texture& texture_sheet, std::map<std::string, int> upgradeCur);
    virtual ~Player();

    //Accessors

    const bool& getInitAttack() const;

    const float getDamageTimer();
    const float getDamageInterval();
    const int getDamage();

    SkillList* getSkillList();

    //Mutators 
    void resetAttackState();
    void setDamageInterval(int newDamageInterval);
    void resetDamageTimer();
    void setAttacking(const bool& attacking);

    void loseHP(const int hp = 1);
    void gainHP(const int hp = 1);


    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);

    void render(sf::RenderTarget& target);
    void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox);

};

#endif
