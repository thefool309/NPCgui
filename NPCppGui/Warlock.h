#pragma once
#include "Character.h"
#include "Structs.h"

class Warlock :
	public Character
{
	int mSpellsKnown;
	int mCantripsKnown;
	int mInvocations;
	SpellSlots mSpellSlots;
public:
	Warlock(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, int lvl, string name, int hitDie = 8)
		: Character(strength, dexterity, constitution, intelligence, wisdom, charisma, lvl, name, hitDie) 
	{
		DetermineInvocations();
		DetermineSpellStats();
	}

	int SpellsKnown() const {
		return mSpellsKnown;
	}

	int Cantrips() const {
		return mCantripsKnown;
	}

	int Invocations() const {
		return mInvocations;
	}

	SpellSlots GetSpellSlots() const {
		return mSpellSlots;
	}

	void DetermineInvocations();
	void DetermineSpellStats();
};

