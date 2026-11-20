#include "Healer.h"
Healer::Healer(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod)
	: Enemy(_id, HEALER, _region, _arrivaltime, _health, _power, _reloadedperiod)
{
}

Healer::~Healer()
{
}

void Healer::Move(int _time){
	MoveOneStep(_time);
}

void Healer::Attack()
{
	// Phase 2: heal enemies within 2 meters
}