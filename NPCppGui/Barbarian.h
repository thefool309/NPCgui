#pragma once
#include "Character.h"
class Barbarian :
	public Character
{
private:
	int mRagePerDay;
public:

	Barbarian(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, int lvl, string name, int hitDie = 12) 
		: Character(strength, dexterity, constitution, intelligence, wisdom, charisma,  lvl, name, hitDie)
	{
		DetermineRage();
	}

	void DetermineRage();
};

