#ifndef skills_h
#define skills_h

#include "imports.h"

class Skills
{

protected: 
    int skillStackCount;
    float skillDuration;
    float damagePerSecond;
    sf::Sprite skillSprite;

public:
    Skills(int skillStackCount = 0, int skillDuration = 0.f, float damagePerSecond = 0.f);
    ~Skills();

    //accessors
    const bool getEffectStatus();
    const int getSkillStackCount();
    const float getSkillDuration();
    const float getDamagePerSecond();


    //mutators
    void increaseSkillCount(int levels = 1);
    void setSkillDuration(float skillDuration); 
    void setDamagePerSecond(float DPS);
};

#endif