#include "Freezer.h"
Freezer::Freezer(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod)
	: Enemy(_id, FREEZEER, _region, _arrivaltime, _health, _power, _reloadedperiod)
	: Enemy(_id, FREEZER, _region, _arrivaltime, _health, _power, _reloadedperiod)
{
}

Freezer::~Freezer()
{
}

void Freezer::Move(int _time){
	MoveOneStep(_time);
}

void Freezer::Act(int _time)
{
	// Phase 2: throw ice on the tower
}
double Freezer::IceAmount()
{
	return (double)Power / Distance;
}