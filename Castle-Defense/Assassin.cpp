#include "Assassin.h"

//hidden for 3 steps after each action
static const int HIDE_DURATION = 3;

Assassin::Assassin(int _id, RegionType _region, int _arrivalTime, double _health, int _power, int _reloadPeriod)
	: Enemy(_id, ASSASSIN, _region, _arrivalTime, _health, _power, _reloadPeriod)
{
}

Assassin::~Assassin()
{
}

void Assassin::Move(int _time)
{
	MoveOneStep(_time);
}

// The assassin attacks like a fighter, then hides for HIDE_DURATION steps.
double Assassin::Act(int _time)
{
	if (!CanAct(_time))
		return 0.0;

	ScheduleNextAction(_time);
	FrozenUntil = _time + HIDE_DURATION;   // reuse the hide window
	return (double)Power / Distance;
}

bool Assassin::IsHidden(int _time)
{
	return _time < FrozenUntil;
}