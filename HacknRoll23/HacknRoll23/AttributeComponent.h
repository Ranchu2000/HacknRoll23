#ifndef attributecomponent_H
#define attributecomponent_H

#include "imports.h"

class AttributeComponent
{
public:
	//Game Stats
	int level;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;

	//Constructor and destructor
	AttributeComponent(int level);
	AttributeComponent(int level, int hpMax, int damage);
	virtual ~AttributeComponent();

	//Accessors
	const bool isDead() const;
	int getCurHealth();
	int getMaxHealth();


	//Mutators
	void resetStats();
	void LevelUp();

	void loseHP(const int hp = 1);
	void gainHP(const int hp = 1);

	void increaseDamage(int levels);
	void increaseHealth(int levels);
};

#endif  