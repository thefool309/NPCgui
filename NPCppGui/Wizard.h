#pragma once
#include "Character.h"
#include "Structs.h"
#include "TheDiceBag.h"

class Wizard :
	public Character
{
private:
	vector<SpellSlots> mSpellSlots;
	int mCantripsKnown;
	int mSpellbook;
	int mArcaneRecovery;
public:
	//constructor
	Wizard(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, int lvl, string name, int hitDie = 6)
		: Character(strength, dexterity, constitution, intelligence, wisdom, charisma, lvl, name, hitDie)
	{
		DetermineSpellStats();
		DetermineArcaneRecovery();
		IsCaster(true);
	}

	//getters
	int Cantrips() const {
		return mCantripsKnown;
	}

	int Spellbook() const {
		return mSpellbook;
	}

	vector<SpellSlots> GetSpellslots() const {
		return mSpellSlots;
	}

	int ArcaneRevocery() const {
		return mArcaneRecovery;
	}

	//function for spell stats
	void DetermineSpellStats();
	void DetermineArcaneRecovery();

};

