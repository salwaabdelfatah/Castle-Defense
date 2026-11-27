#include "Freezer.h"

Freezer::Freezer(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod)
	: Enemy(_id, FREEZER, _region, _arrivaltime, _health, _power, _reloadedperiod)
{
}

Freezer::~Freezer()
{
}

void Freezer::Move(int _time)
{
	MoveOneStep(_time);
}

// Freezer's action is throwing ice on its tower.
// It returns the ice amount, and the tower decides whether to freeze.
double Freezer::Act(int _time)
{
	if (!CanAct(_time))
		return 0.0;

	ScheduleNextAction(_time);
	return IceAmount();
}

// Spec: ice amount = enemy power / enemy distance.
// The tower rejects any shot at or above FREEZE_THRESHOLD.
double Freezer::IceAmount()
{
	return (double)Power / Distance;
}


