#ifndef skilllist_H
#define skilllist_H

#include "Skills.h"
#include "BurnSkill.h"
#include "PiercingSkill.h"

class SkillList
{
private:
    BurnSkill burn;
    PiercingSkill pierce;

public:

    //Constructor + Destructor
    SkillList();
    ~SkillList();

    //accessors 
    Skills& getBurnSkill();
    Skills& getPiercingSkill();

    //Mutators
    void increaseBurnLevel(int levels = 1); //increase 1 level by default
    void increasePierceLevel(int levels = 1); //increase 1 level by default

};

#endif