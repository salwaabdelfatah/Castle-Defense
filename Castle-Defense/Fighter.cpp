#include "Fighter.h"
Fighter::Fighter(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod)
	: Enemy(_id, FIGHTER, _region, _arrivaltime, _health, _power, _reloadedperiod)
{
}

Fighter::~Fighter()
{
}

void Fighter::Move(int _time){
	MoveOneStep(_time);
}

void Fighter::Act(int _time)
{
	// Phase 2
}