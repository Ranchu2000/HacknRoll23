#include "Skills.h"

Skills::Skills(int skillStackCount, int skillDuration, float damagePerSecond) : skillStackCount(skillStackCount), skillDuration(skillDuration), damagePerSecond(damagePerSecond)
{
}

Skills::~Skills()
{
}

//Accessors
const bool Skills::getEffectStatus()
{
    if (this->skillStackCount > 0)
        return true;
    else
        return false;
}

const int Skills::getSkillStackCount()
{
    return this->skillStackCount;
}

const float Skills::getSkillDuration()
{
    return this->skillDuration;
}

const float Skills::getDamagePerSecond()
{
    return this->damagePerSecond;
}

//mutators
void Skills::increaseSkillCount(int levels)
{
    this->skillStackCount += levels;
}

void Skills::setSkillDuration(float skillDuration)
{
    this->skillDuration = skillDuration;
}

void Skills::setDamagePerSecond(float DPS)
{
    this->damagePerSecond = DPS;
}