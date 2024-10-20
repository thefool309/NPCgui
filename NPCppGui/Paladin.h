#pragma once
#include "Character.h"
class Paladin :
	public Character
{
private:
	//member fields
	std::vector<SpellSlots> mSpellSlots;
	int mLayOnHands;
public:
	//constructors
	Paladin(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, int lvl, string name, int hitDie = 10)
		: Character(strength, dexterity, constitution, intelligence, wisdom, charisma, lvl, name, hitDie) 
	{
		SpellStats();
		IsCaster(true);
	}
		//accessors
	std::vector<SpellSlots> SpellSlots() const { return mSpellSlots; }
	int LayOnHands() const { return mLayOnHands; }
		//mutators
private:
	void SpellStats();

};

