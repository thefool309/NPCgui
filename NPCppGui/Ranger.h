#pragma once
#include "Character.h"
#include "Utils.h"
class Ranger :
    public Character
{
private:
    std::vector<SpellSlots> mSpellSlots;
    std::string mFavouredEnemy;
public:
    //constructor
    Ranger(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, int lvl, string name, int hitDie = 10)
        : Character(strength, dexterity, constitution, intelligence, wisdom, charisma, lvl, name, hitDie)
    {
        SpellStats();
        FavouredEnemy();
        IsCaster(true);
    }
    //accessors
    std::vector<SpellSlots> SpellSlots() const { return mSpellSlots; }

    //mutators
    void SpellStats();
    void FavouredEnemy();
};

