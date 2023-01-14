#ifndef burnskill_h
#define burnskill_h

#include "Skills.h"

class BurnSkill : public Skills
{
public:
    BurnSkill(int skillDuration, float damagePerSecond);
};

#endif