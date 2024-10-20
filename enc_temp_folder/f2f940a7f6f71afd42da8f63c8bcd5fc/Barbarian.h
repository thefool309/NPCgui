#pragma once
#include "Character.h"
class Barbarian :
	public Character
{
private:
	int mRagePerDay;
public:

	Barbarian() : mRagePerDay(DetermineRage()), Character() {
		
	}

	Barbarian(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, int lvl, int hitDie, string name) 
		: mRagePerDay(DetermineRage()), Character(strength, dexterity, constitution, intelligence, wisdom, charisma,  lvl, hitDie, name)
	{
		
	}

	int DetermineRage();
};

