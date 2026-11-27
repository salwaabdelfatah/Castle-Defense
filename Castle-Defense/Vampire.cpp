#include "Vampire.h"

Vampire::Vampire(int _id, RegionType _region, int _arrivalTime, double _health, int _power, int _reloadPeriod)
	: Enemy(_id, VAMPIRE, _region, _arrivalTime, _health, _power, _reloadPeriod)
{
}

Vampire::~Vampire()
{
}

void Vampire::Move(int _time)
{
	MoveOneStep(_time);
}

// Vampire attacks the tower and heals itself by the same amount.
// Returns the damage, and the tower applies it (same as Fighter).
double Vampire::Act(int _time)
{
	if (!CanAct(_time))
		return 0.0;

	ScheduleNextAction(_time);

	double damage = (double)Power / Distance;

	// Heal by the damage dealt, never above original health (team decision)
	double newHealth = Health + damage;
	SetHealth(newHealth > OriginalHealth ? OriginalHealth : newHealth);

	return damage;
}