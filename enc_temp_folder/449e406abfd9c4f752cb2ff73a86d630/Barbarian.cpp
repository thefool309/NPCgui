#include "Barbarian.h"

int Barbarian::DetermineRage()
{
	int ragePerDay;
	if (Lvl() < 3)
		ragePerDay = 2;
	else if (Lvl() >= 3 && Lvl() < 6)
		ragePerDay = 3;
	else if (Lvl() >= 6 && Lvl() < 12)
		ragePerDay = 4;
	else if (Lvl() >= 12 && Lvl() < 17)
		ragePerDay = 5;
	else
		ragePerDay = 6;
	return ragePerDay;
}
