#include "SkillList.h"
#include "BurnSkill.h"
#include "PiercingSkill.h"


//Constructor and Destructor
SkillList::SkillList() : burn(2, 10), pierce()
{

}

SkillList::~SkillList()
{

}

//accessors 
Skills& SkillList::getBurnSkill()
{
    return this->burn;
}

Skills& SkillList::getPiercingSkill()
{
    return this->pierce;
}

//mutators
void SkillList::increaseBurnLevel(int levels)
{
    this->burn.increaseSkillCount(levels);
}

void SkillList::increasePierceLevel(int levels)
{
    this->pierce.increaseSkillCount(levels);
}